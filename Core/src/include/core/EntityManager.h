#pragma once
#include "ECS.h"
#include <queue>
#include <array>
#include <cassert>

namespace Core
{
	class EntityManager {
	public:
		EntityManager() {
			for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
				mAvailableEntities.push(entity);
			}
		}

		Entity createEntity() {
			assert(mLivingEntityCount < MAX_ENTITIES && "Max entities reached.");
			Entity id = mAvailableEntities.front();
			mAvailableEntities.pop();
			++mLivingEntityCount;

			return id;

		}

		void destroyEntity(Entity entity) {
			assert(entity < MAX_ENTITIES && "Entity ID out of bounds.");

			mSignatures[entity].reset();
			mAvailableEntities.push(entity);
			--mLivingEntityCount;
		}

		void setSignature(Entity entity, Signature signature) {
			assert(entity < MAX_ENTITIES && "Entity ID out of bounds.");
			mSignatures[entity] = signature;
		}

		Signature getSignature(Entity entity) const {
			assert(entity < MAX_ENTITIES && "Entity ID out of bounds.");
			return mSignatures[entity];
		}

	private:
		std::queue<Entity> mAvailableEntities;
		std::array<Signature, MAX_ENTITIES> mSignatures{};
		uint32_t mLivingEntityCount{};

	};
}
