//
// Created by Sp4rk on 21-09-17.
//

#ifndef CES_SYSTEMBASE_H
#define CES_SYSTEMBASE_H

#include <vector>
#include "Entity.h"

class Scene;

class SystemBase
{
public:
    SystemBase(int mask, Scene *scene);

    // TODO: It is like an ASSERT.. perhaps some sort of "Assert"ing class could be made for this purpose
    bool match(int entityMask, int requiredMask);

    void add(Entity *entity);

    void remove(Entity *entity);

    int getMask();

    Scene *getScene();

    void setMask(int mask);

    void setScene(Scene &scene);

    std::vector<Entity *> &getMatchingEntities();

protected:
    // TODO: "std::bitset" instead of "int"
    int mask_;
    Scene *scene_;
    std::vector<Entity *> matchingEntities_;
};

#endif //CES_SYSTEMBASE_H
