#pragma once
#include "ECS.h"
#include "ComponentArray.h"
#include <memory>
#include <string>

namespace Core
{
	class ComponentManager {
	public:
		// Register a component type with the ComponentManager by adding it to the component map and creating a ComponentArray for it.
		template<typename T>
		void registerComponent() {
			std::string typeName = typeid(T).name();
			assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Component type already registered.");
			// Add this component type to the component map
			mComponentTypes.insert({ typeName, mNextComponentType });
			// Create a ComponentArray pointer for this component type
			mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
			// Increment the next component type
			++mNextComponentType;
		}

		//Returns the component type identifier for the given component type T.
		template<typename T>
		ComponentType getComponentType() {
			std::string typeName = typeid(T).name();
			assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component type not registered.");
			return mComponentTypes[typeName];
		}

		template<typename T>
		void addComponent(Entity entity, T component) {
			//Gets pointer to the ComponentArray for the component type T and inserts the component data for the entity.
			auto componentArray = getComponentArray<T>();
			componentArray->insertData(entity, component);
		}

		template<typename T>
		void removeComponent(Entity entity) {
			//Gets pointer to the ComponentArray for the component type T and removes the component data for the entity.
			auto componentArray = getComponentArray<T>();
			componentArray->removeData(entity);
		}

		template<typename T>
		T& getComponent(Entity entity) {
			//Gets pointer to the ComponentArray for the component type T and retrieves the component data for the entity.
			auto componentArray = getComponentArray<T>();
			return componentArray->getData(entity);
		}

		void EntityDestroyed(Entity entity) {
			//Iterates through all component arrays and calls EntityDestroyed to remove the entity from each component array.
			for (auto& pair : mComponentArrays) {
				pair.second->EntityDestroyed(entity);
			}
		}


	private:
		std::unordered_map<std::string, ComponentType> mComponentTypes{};
		std::unordered_map<std::string, std::shared_ptr<IComponentArray>> mComponentArrays{};

		ComponentType mNextComponentType{};

		template<typename T>
		std::shared_ptr<ComponentArray<T>> getComponentArray() {
			std::string typeName = typeid(T).name();
			assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component type not registered.");
			return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
		}
	};
}
