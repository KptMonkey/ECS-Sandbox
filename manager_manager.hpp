#pragma once

#include "system_manager.hpp"
#include "entity_manager.hpp"
#include "component_manager.hpp"
#include <memory>

class ManagerManager {

    public:
        Entity createEntity() {
            return mEntityManager->createEntity();
        }

        void destroyEntity(Entity e) {
            mEntityManager->destroyEntity(e);
            mComponentManager->entityDestroyed(e);
            mSystemManager->entityDestroyed(e);
        }

        template<typename T>
        void registerComponent() {
            mComponentManager->registerComponent<T>();
        }

        template<typename T>
        void addComponent(Entity entity, T component) {
            mComponentManager->addComponent<T>(entity, component);

            auto signature = mEntityManager->getSignature(entity);
            signature.set(mComponentManager->getComponentType<T>(), true);
            mEntityManager->setSignature(entity, signature);

            mSystemManager->entitySignatureChanged(entity, signature);
        }

        template<typename T>
        void removeComponent(Entity e) {
            mComponentManager->removeComponent<T>(e);

            auto signature = mEntityManager->getSignature(e);
            signature.set(mComponentManager->getComponentType<T>(), false);
            mEntityManager->setSignature(e, signature);

            mSystemManager->entitySignatureChanged(e, signature);
        }

        template<typename T>
        T& GetComponent(Entity e) {
            return mComponentManager->getComponent<T>(e);
        }

        template<typename T>
        ComponentType GetComponentType() {
            return mComponentManager->getComponentType<T>();
        }


        template<typename T>
        std::shared_ptr<T> RegisterSystem() {
            return mSystemManager->registerSystem<T>();
        }

        template<typename T>
        void SetSystemSignature(Signature signature) {
            mSystemManager->setSignature<T>(signature);
        }

    private:
        std::unique_ptr<SystemManager>    mSystemManager    = std::make_unique<SystemManager>();
        std::unique_ptr<ComponentManager> mComponentManager = std::make_unique<ComponentManager>();
        std::unique_ptr<EntityManager>    mEntityManager    = std::make_unique<EntityManager>();
};
