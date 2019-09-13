#include <iostream>
#include "entity_manager.hpp"

int main() {
    EntityManager em;
    auto e = em.createEntity();
    em.destroyEntity(e);
}
