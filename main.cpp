#include "manager_manager.hpp"
#include "print_system.hpp"

ManagerManager manager;

int main() {
    manager.registerComponent<Print>();
    auto printSystem = manager.registerSystem<PrintSystem>();

    Signature signature;
    signature.set(manager.getComponentType<Print>());
    manager.setSystemSignature<PrintSystem>(signature);

    std::vector<Entity> entities(MAX_ENTITIES);
    for(auto& e : entities) {
        e = manager.createEntity();
        Print p;
        p.output = e;
        manager.addComponent<Print>(e, p);
    }

    while(true) {
        printSystem->update();
    }

}
