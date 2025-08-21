#pragma once
#include "ECS.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include <memory>

namespace Core
{
	class Coordinator {
	public:
		void Init() {
			mEntityManager = std::make_unique<EntityManager>();
			mComponentManager = std::make_unique<ComponentManager>();
			mSystemManager = std::make_unique<SystemManager>();
		}

		Entity createEntity() {
			return mEntityManager->createEntity();
		}

		void destroyEntity(Entity entity) {
			mEntityManager->destroyEntity(entity);
			mComponentManager->EntityDestroyed(entity);
			mSystemManager->entityDestroyed(entity);
		}

		template<typename T>
		void registerComponent() {
			mComponentManager->registerComponent<T>();
		}

		template<typename T>
		void addComponent(Entity entity, T component) {
			mComponentManager->addComponent<T>(entity, component);
			Signature signature = mEntityManager->getSignature(entity);
			signature.set(mComponentManager->getComponentType<T>(), true);
			mEntityManager->setSignature(entity, signature);
			mSystemManager->entitySignatureChanged(entity, signature);
		}

		template<typename T>
		void removeComponent(Entity entity) {
			mComponentManager->removeComponent<T>(entity);
			Signature signature = mEntityManager->getSignature(entity);
			signature.set(mComponentManager->getComponentType<T>(), false);
			mEntityManager->setSignature(entity, signature);
			mSystemManager->entitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& getComponent(Entity entity) {
			return mComponentManager->getComponent<T>(entity);
		}

		template<typename T>
		ComponentType getComponentType() {
			return mComponentManager->getComponentType<T>();
		}

		template<typename T>
		std::shared_ptr<T> registerSystem() {
			return mSystemManager->registerSystem<T>();
		}

		template<typename T>
		void setSystemSignature(Signature signature) {
			mSystemManager->setSignature<T>(signature);
		}
	private:
		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<ComponentManager> mComponentManager;
		std::unique_ptr<SystemManager> mSystemManager;
	};
}