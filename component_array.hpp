#pragma once

#include "entity.hpp"
#include <array>
#include <unordered_map>

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(Entity e) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
    void insertData(Entity e, T component) {
       int newIndex = mSize;
       mEntityToIndexMap[e] = newIndex;
       mIndexToEntityMap[newIndex] = e;
       mComponentArray[newIndex] = component;
       ++mSize;
    }

    void removeData(Entity e) {
        auto indexOfRemovedEntity = mEntityToIndexMap[e];
        auto indexOfLastElement = mSize - 1;
        mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

        Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
        mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        mEntityToIndexMap.erase(e);
        mIndexToEntityMap.erase(indexOfLastElement);

        --mSize;
    }

    T& getData(Entity entity)
    {
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

        // Return a reference to the entity's component
        return mComponentArray[mEntityToIndexMap[entity]];
    }

    void entityDestroyed(Entity e) override
    {
        if (mEntityToIndexMap.find(e) != mEntityToIndexMap.end())
        {
            // Remove the entity's component if it existed
            removeData(e);
        }
    }

private:

    int mSize = 0;
    std::array<T, MAX_ENTITIES> mComponentArray;

    // Map from an entity ID to an array index.
    std::unordered_map<Entity, int> mEntityToIndexMap;

    // Map from an array index to an entity ID.
    std::unordered_map<int, Entity> mIndexToEntityMap;
};
