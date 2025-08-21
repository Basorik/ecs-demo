#pragma once
#include "ECS.h"
#include <stack>
#include <array>
#include <cassert>

namespace Core
{
	class EntityManager {
	public:
		EntityManager() {
			// Initialize the queue with all possible entity IDs
			for (Entity entity = MAX_ENTITIES - 1; entity != (Entity)-1; --entity) {
				mAvailableEntities.push(entity);
			}
		}

		Entity createEntity() {
			assert(mLivingEntityCount < MAX_ENTITIES && "Max entities reached.");
			Entity id = mAvailableEntities.top();
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
		std::stack<Entity> mAvailableEntities;
		std::array<Signature, MAX_ENTITIES> mSignatures{};
		uint32_t mLivingEntityCount{};

	};
}
