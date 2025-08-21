#pragma once

#include "ECS.h"
#include "Logger.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeinfo>

namespace Core {

    // Forward declare ComponentManager to be used in Coordinator
    class IComponentManager {
    public:
        virtual ~IComponentManager() = default;
    };

    template<typename T>
    class ComponentManager : public IComponentManager {
    private:
        // Array of components, indexed by entity ID.
        std::vector<T> mComponents;
        // Map from entity ID to component index.
        std::unordered_map<Entity, size_t> mEntityToIndexMap;
        // Map from component index to entity ID.
        std::unordered_map<size_t, Entity> mIndexToEntityMap;

    public:
        ComponentManager() : mComponents(MAX_ENTITIES) {}

        void addComponent(Entity entity, T component) {
            size_t newIndex = mEntityToIndexMap.size();
            mEntityToIndexMap[entity] = newIndex;
            mIndexToEntityMap[newIndex] = entity;
            mComponents[newIndex] = component;
        }

        T& getComponent(Entity entity) {
            return mComponents[mEntityToIndexMap[entity]];
        }
    };


    /**
     * @class Coordinator
     * @brief The main ECS class that manages entities, components, and systems.
     */
    class Coordinator {
    private:
        // Entity management
        std::vector<Entity> mAvailableEntities{};
        uint32_t mLivingEntityCount = 0;

        // Component management
        std::unordered_map<const char*, ComponentType> mComponentTypes{};
        std::unordered_map<const char*, std::shared_ptr<IComponentManager>> mComponentManagers{};
        ComponentType mNextComponentType = 0;

        // System management
        std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
        std::unordered_map<const char*, Signature> mSystemSignatures{};
        std::vector<Signature> mEntitySignatures;


    public:
        Coordinator() : mEntitySignatures(MAX_ENTITIES) {
            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
                mAvailableEntities.push_back(entity);
            }
        }

        // Entity methods
        Entity createEntity() {
            if (mLivingEntityCount >= MAX_ENTITIES) {
                /*GameLog("Error", "Too many entities in existence.");*/
                // In a real game, you might handle this more gracefully
                throw std::runtime_error("Max entities reached.");
            }
            Entity id = mAvailableEntities.back();
            mAvailableEntities.pop_back();
            ++mLivingEntityCount;
            return id;
        }

        // Component methods
        template<typename T>
        void registerComponent() {
            const char* typeName = typeid(T).name();
            mComponentTypes[typeName] = mNextComponentType;
            mComponentManagers[typeName] = std::make_shared<ComponentManager<T>>();
            ++mNextComponentType;
        }

        template<typename T>
        void addComponent(Entity entity, T component) {
            const char* typeName = typeid(T).name();
            getComponentManager<T>()->addComponent(entity, component);

            auto& signature = mEntitySignatures[entity];
            signature.set(mComponentTypes[typeName], true);

            // Notify systems that an entity's signature has changed
            for (auto const& [key, val] : mSystems) {
                auto const& system = val;
                auto const& systemSignature = mSystemSignatures[mComponentTypes[key]];
                if ((signature & systemSignature) == systemSignature) {
                    system->mEntities.insert(entity);
                }
            }
        }

        template<typename T>
        T& getComponent(Entity entity) {
            return getComponentManager<T>()->getComponent(entity);
        }

        template<typename T>
        ComponentType getComponentType() {
            const char* typeName = typeid(T).name();
            return mComponentTypes[typeName];
        }

        // System methods
        template<typename T>
        std::shared_ptr<T> registerSystem() {
            const char* typeName = typeid(T).name();
            auto system = std::make_shared<T>();
            mSystems[typeName] = system;
            return system;
        }

        template<typename T>
        void setSystemSignature(Signature signature) {
            const char* typeName = typeid(T).name();
            mSystemSignatures[typeName] = signature;
        }

    private:
        template<typename T>
        std::shared_ptr<ComponentManager<T>> getComponentManager() {
            const char* typeName = typeid(T).name();
            return std::static_pointer_cast<ComponentManager<T>>(mComponentManagers[typeName]);
        }
    };

} //