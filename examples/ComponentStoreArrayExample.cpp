//
// Created by Sp4rk on 22-09-17.
//

#include "ComponentStoreArrayExemple.h"

void ComponentStoreArrayExample::showExample()
{
    ComponentStoreArray<Sprite> transformComponents(MAX_ENTITIES);

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
    auto componentA = transformComponents.get(2000);
    std::cout << componentA.entityId << " with w = " << componentA.w << std::endl;


    std::cout << "o---------------------------------------o" << std::endl;
    std::cout << "| Remove component with entityId = 2000 |" << std::endl;
    std::cout << "o---------------------------------------o" << std::endl;
    transformComponents.removeComponent(2000);

    std::cout << "==> STORE <==" << std::endl;
    auto componentB = transformComponents.get(2000);
    std::cout << componentB.entityId << " with w = " << componentB.w << std::endl;
}
