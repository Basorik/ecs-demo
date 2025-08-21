#pragma once
#include "ECS.h"
#include <array>
#include <unordered_map>

namespace Core
{
	class IComponentArray {
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray {
	public:
		void insertData(Entity entity, T component) {
			assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component already exists for this entity.");

			size_t index = mSize;
			mEntityToIndexMap[entity] = index;
			mIndexToEntityMap[index] = entity;
			mComponentArray[index] = component;
			++mSize;
		}

		void removeData(Entity entity) {
			assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Component does not exist for this entity.");
			size_t indexOfRemoved = mEntityToIndexMap[entity];
			size_t indexOfLastElement = mSize - 1;
			mComponentArray[indexOfRemoved] = mComponentArray[indexOfLastElement];

			Entity lastElementEntity = mIndexToEntityMap[indexOfLastElement];
			mEntityToIndexMap[lastElementEntity] = indexOfRemoved;
			mIndexToEntityMap[indexOfRemoved] = lastElementEntity;
			mEntityToIndexMap.erase(entity);
			mIndexToEntityMap.erase(indexOfLastElement);
			--mSize;
		}

		T& getData(Entity entity) {
			assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Component does not exist for this entity.");
			return mComponentArray[mEntityToIndexMap[entity]];
		}

		void EntityDestroyed(Entity entity) override {
			if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
				removeData(entity);
			}
		}
	private:
		std::array<T, MAX_ENTITIES> mComponentArray{};

		std::unordered_map<Entity, size_t> mEntityToIndexMap{};
		std::unordered_map<size_t, Entity> mIndexToEntityMap{};

		size_t mSize{};
	};
}
