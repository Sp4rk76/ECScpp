//
// Created by Sp4rk on 22-08-17.
//

#ifndef CES_ENTITYMANAGER_H
#define CES_ENTITYMANAGER_H

#include "texturing/TextureManager.h"

class Scene;

class EntityManagerOld
{
public:
    explicit EntityManagerOld(Scene &scene);

    Entity *createEntity();

    // TODO: create entity by ID

    Entity *createPlayer(int x, int y);

    Entity *createBall(int x, int y);

    Entity *createBackground(int x = 0, int y = 0);

    void destroyEntity(Entity *entity);

    void registerAs(Entity *entity);

    void unregister(Entity *entity);

private:
    static uint32_t ID;

    Scene &scene_;

    std::vector<Entity> entities_;
};

#endif //CES_ENTITYMANAGER_H
