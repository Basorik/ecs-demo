#pragma once
#include "ECS.h"
#include <unordered_map>
#include <memory>


namespace Core
{

	class SystemManager {
	public:
		template<typename T>
		std::shared_ptr<T> registerSystem() {
			std::string typeName = typeid(T).name();
			assert(mSystemSignatures.find(typeName) == mSystemSignatures.end() && "System type already registered.");
			// Create a new system of type T and store it in the systems map
			auto system = std::make_shared<T>();
			mSystems.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void setSignature(Signature signature) {
			std::string typeName = typeid(T).name();
			assert(mSystemSignatures.find(typeName) == mSystemSignatures.end() && "System signature already set.");
			// Set the signature for the system type T
			mSystemSignatures.insert({ typeName, signature });
		}

		void entityDestroyed(Entity entity) {
			// Iterate through all systems and remove the entity from their entity sets
			for (auto& pair : mSystems) {
				const auto& system = pair.second;
				system->mEntities.erase(entity);
			}
		}

		void entitySignatureChanged(Entity entity, Signature signature) {
			for (const auto& pair : mSystems) {
				const auto& type = pair.first;
				const auto& system = pair.second;
				const auto& systemSignature = mSystemSignatures[type];

				if ((signature & systemSignature) == systemSignature) {
					// The entity matches the system's signature, add it to the system
					system->mEntities.insert(entity);
				}
				else {
					// The entity does not match the system's signature, remove it from the system
					system->mEntities.erase(entity);
				}
			}
		}
	private:
		std::unordered_map<std::string, Signature> mSystemSignatures{};
		std::unordered_map<std::string, std::shared_ptr<System>> mSystems{};
	};
}