#pragma once
#include "entity.hpp"
#include <set>

class System {
public:
    std::set<Entity> mEntities;
};
