#pragma once

#include "component.hpp"
#include "component_array.hpp"
#include "entity.hpp"

#include <typeinfo>
#include <memory>
#include <unordered_map>

class ComponentManager {
public:
    template<typename T>
    void registerComponent() {
        auto typeName = typeid(T).name();
        mComponentTypes.insert({typeName, mNextComponentType});
        mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
        ++mNextComponentType;
    }

    template<typename T>
    ComponentType getComponentType() {
        auto typeName = typeid(T).name();
        return mComponentTypes[typeName];
    }

    template<typename T>
    void addComponent(Entity e, T component) {
        auto compArray = getComponentArray<T>();
        compArray->insertData(e, component);
    }

    template<typename T>
    void removeComponent(Entity e) {
        auto compArray = getComponentArray<T>();
        compArray->removeData(e);
    }

    template<typename T>
    T& getComponent(Entity e) {
        auto compArray = getComponentArray<T>();
        return compArray->getData(e);
    }

    void
    entityDestroyed(Entity e) {
        for (auto const& pair : mComponentArrays) {
            pair.second->entityDestroyed(e);
        }
    }

private:
    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray() {
        auto typeName = typeid(T).name();
        return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
    }

    std::unordered_map<const char*, ComponentType>                    mComponentTypes{};
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};
    ComponentType                                                     mNextComponentType{};
};
