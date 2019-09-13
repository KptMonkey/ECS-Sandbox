#include "entity.hpp"
#include "component.hpp"

#include <deque>
#include <array>
#include <stdio.h>

class EntityManager
{
    public:
    EntityManager() {
        mEntities.resize(MAX_ENTITIES);
        for(int i=0; i<MAX_ENTITIES; ++i)
            mEntities[i]=i;
    }

    Entity createEntity() {
        auto e = mEntities.front();
        mEntities.pop_front();
        ++mLivingEntityCount;
        printf("CreateEntity \n");
        return e;
    }

    void destroyEntity(Entity e) {
        mEntities.push_back(e);
        mSignatures[e].reset();
        --mLivingEntityCount;
        printf("DestroyEntity \n");
    }

    void setSignature(Entity e, Signature s) {
        mSignatures[e] = s;
    }

    Signature getSignature(Entity e) {
        return mSignatures[e];
    }

    private:
    std::deque<Entity> mEntities;
    std::array<Signature, MAX_ENTITIES> mSignatures{};
    uint32_t mLivingEntityCount{};
};
