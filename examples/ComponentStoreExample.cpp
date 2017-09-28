//
// Created by Sp4rk on 16-09-17.
//

#include "ComponentStoreExample.h"


void ComponentStoreExample::showExample()
{
    ComponentStore<Sprite> transformComponents;

    Sprite s1, s2, s3, s4;

    s1.w = 11;
    s1.entityId = 1000;

    s2.w = 22;
    s2.entityId = 2000;

    s3.w = 33;
    s3.entityId = 3000;

    s4.w = 44;
    s4.entityId = 4000;

    transformComponents.addComponent(1000, s1);
    transformComponents.addComponent(2000, s2);
    transformComponents.addComponent(3000, s3);
    transformComponents.addComponent(4000, s4);

    std::cout << "==> STORE <==" << std::endl;
    for(auto& component : transformComponents.getAll())
    {
        std::cout << component.entityId << " with w = " << component.w << std::endl;
    }

    std::cout << "==> STORE_MAP <==" << std::endl;
    std::cout << "entityID ; storeID" << std::endl;
    for(auto& pair : transformComponents.getMap())
    {
        std::cout << pair.first << " ; " << pair.second << std::endl;
    }

    std::cout << "o---------------------------------------o" << std::endl;
    std::cout << "| Remove component with entityId = 2000 |" << std::endl;
    std::cout << "o---------------------------------------o" << std::endl;
    transformComponents.removeComponent(2000);

    std::cout << "==> STORE <==" << std::endl;
    for(auto& component : transformComponents.getAll())
    {
        std::cout << component.entityId << " with w = " << component.w << std::endl;
    }

    std::cout << "==> STORE_MAP <==" << std::endl;
    std::cout << "entityID ; storeID" << std::endl;
    for(auto& pair : transformComponents.getMap())
    {
        std::cout << pair.first << " ; " << pair.second << std::endl;
    }

    std::cout << "MODIFYING VECTOR FROM ANOTHER PART OF THE PROGRAM" << std::endl;
    Sprite *s0 = &transformComponents.get(1000);
    s0->w = 9999;
    std::cout << transformComponents.get(1000).w << std::endl;
}