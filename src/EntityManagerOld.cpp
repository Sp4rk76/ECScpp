//
// Created by Sp4rk on 22-08-17.
//

#include "Entity.h"
#include "Scene.h"
#include "EntityManagerOld.h"
#include "display/Screen.h"

uint32_t EntityManagerOld::ID = 0;

EntityManagerOld::EntityManagerOld(Scene &scene) : scene_(scene) {}

Entity *EntityManagerOld::createEntity()
{
    Entity *entity = new Entity();
    entity->id = ++ID;
    return entity;
}

Entity *EntityManagerOld::createPlayer(int x, int y)
{
    Entity *entity = createEntity();

    int mask = 0;
    Object2D component2D;
    Rigidbody2D rigidbody2D;
    BoxCollider2D boxCollider2D;
    CircleCollider2D circleCollider2D;
    Sprite sprite;

    mask = SPRITE | PLAYER | OBJECT2D | PHYSICS2D | BOXCOLLIDER2D;

    component2D.size.w = 32;
    component2D.size.h = 32;
    component2D.transform.position.x = x;
    component2D.transform.position.y = y;

    rigidbody2D.velocity.x = 0;
    rigidbody2D.velocity.y = 0;

    boxCollider2D.offsetX = 0;
    boxCollider2D.offsetY = 0;
    boxCollider2D.center.x = component2D.transform.position.x + (component2D.size.w / 2);
    boxCollider2D.center.y = component2D.transform.position.y + (component2D.size.h / 2);
    boxCollider2D.x = boxCollider2D.center.x - (boxCollider2D.w / 2) + boxCollider2D.offsetX;
    boxCollider2D.y = boxCollider2D.center.y - (boxCollider2D.h / 2) + boxCollider2D.offsetY;
    boxCollider2D.w = 150;
    boxCollider2D.h = 32;
    boxCollider2D.isVisible = true;

    circleCollider2D.offsetX = 0;
    circleCollider2D.offsetY = 0;
    circleCollider2D.center.x = component2D.transform.position.x + (component2D.size.w / 2);
    circleCollider2D.center.y = component2D.transform.position.y + (component2D.size.h / 2);
    circleCollider2D.x = circleCollider2D.center.x - (circleCollider2D.w / 2) + circleCollider2D.offsetX;
    circleCollider2D.y = circleCollider2D.center.y - (circleCollider2D.h / 2) + circleCollider2D.offsetY;
    circleCollider2D.w = 32;
    circleCollider2D.h = 32;
    circleCollider2D.radius = circleCollider2D.w / 2;
    circleCollider2D.isVisible = true;

    sprite.texture = TextureManager::getInstance()->getTexture("player");
    sprite.w = 32;
    sprite.h = 32;

    scene_.maskStore_.addComponent(entity->id, mask);
    scene_.componentBaseStore_.addComponent(entity->id, component2D);
    scene_.rigidbody2DStore_.addComponent(entity->id, rigidbody2D);
    scene_.boxCollider2DStore_.addComponent(entity->id, boxCollider2D);
    scene_.circleCollider2DStore_.addComponent(entity->id, circleCollider2D);
    scene_.spriteStore_.addComponent(entity->id, sprite);

    registerAs(entity);
}

Entity *EntityManagerOld::createBall(int x, int y)
{
    Entity *entity = createEntity();

    int mask = 0;
    Object2D component2D;
    Rigidbody2D rigidbody2D;
    BoxCollider2D boxCollider2D;
    CircleCollider2D circleCollider2D;
    Sprite sprite;

    mask = SPRITE | OBJECT2D | PHYSICS2D | BOXCOLLIDER2D;

    component2D.size.w = 32;
    component2D.size.h = 32;
    component2D.transform.position.x = x;
    component2D.transform.position.y = y;

    rigidbody2D.velocity.x = 0;
    rigidbody2D.velocity.y = 1;

    boxCollider2D.offsetX = 0;
    boxCollider2D.offsetY = 0;
    boxCollider2D.center.x = component2D.transform.position.x + (component2D.size.w / 2);
    boxCollider2D.center.y = component2D.transform.position.y + (component2D.size.h / 2);
    boxCollider2D.x = boxCollider2D.center.x - (boxCollider2D.w / 2) + boxCollider2D.offsetX;
    boxCollider2D.y = boxCollider2D.center.y - (boxCollider2D.h / 2) + boxCollider2D.offsetY;
    boxCollider2D.w = 32;
    boxCollider2D.h = 32;
    boxCollider2D.isVisible = true;

    circleCollider2D.offsetX = 0;
    circleCollider2D.offsetY = 0;
    circleCollider2D.center.x = component2D.transform.position.x + (component2D.size.w / 2);
    circleCollider2D.center.y = component2D.transform.position.y + (component2D.size.h / 2);
    circleCollider2D.x = circleCollider2D.center.x - (circleCollider2D.w / 2) + circleCollider2D.offsetX;
    circleCollider2D.y = circleCollider2D.center.y - (circleCollider2D.h / 2) + circleCollider2D.offsetY;
    circleCollider2D.w = 32;
    circleCollider2D.h = 32;
    circleCollider2D.radius = circleCollider2D.w / 2;
    circleCollider2D.isVisible = true;

    if ((mask & CIRCLECOLLIDER2D) == CIRCLECOLLIDER2D)
    {
        sprite.texture = TextureManager::getInstance()->getTexture("background");
    }
    else
    {
        sprite.texture = TextureManager::getInstance()->getTexture("ball");
    }
    sprite.w = 32;
    sprite.h = 32;

    scene_.maskStore_.addComponent(entity->id, mask);
    scene_.componentBaseStore_.addComponent(entity->id, component2D);
    scene_.rigidbody2DStore_.addComponent(entity->id, rigidbody2D);
    scene_.boxCollider2DStore_.addComponent(entity->id, boxCollider2D);
    scene_.circleCollider2DStore_.addComponent(entity->id, circleCollider2D);
    scene_.spriteStore_.addComponent(entity->id, sprite);

    registerAs(entity);
}

Entity *EntityManagerOld::createBackground(int x, int y)
{
    Entity *entity = createEntity();

    int mask = SPRITE | OBJECT2D;
    Sprite sprite;

    // TODO: find a way to improve this.. or change the concept => relative to the scene's w/h instead of the screen w/h.
    Screen *screen = scene_.getGame()->getScreen();

    sprite.texture = TextureManager::getInstance()->getTexture("background");
    sprite.w = screen->getWidth();
    sprite.h = screen->getHeight();

    scene_.maskStore_.addComponent(entity->id, mask);
    scene_.spriteStore_.addComponent(entity->id, sprite);

    registerAs(entity);

    delete screen;
    screen = NULL;
}

void EntityManagerOld::destroyEntity(Entity *entity)
{
    // TODO: Reset/Remove mask & components
    // 1. Get components for this entity
    // 2. Remove them from the stores

    // TODO: destroy the entity ?
    unregister(entity);

}

void EntityManagerOld::registerAs(Entity *entity)
{
    for (Updater *updater : scene_.updaters_)
    {
        updater->add(entity);
    }
    for (Renderer *renderer : scene_.renderers_)
    {
        renderer->add(entity);
    }
}

void EntityManagerOld::unregister(Entity *entity)
{
    for (Updater *updater : scene_.updaters_)
    {
        updater->remove(entity);
    }
    for (Renderer *renderer : scene_.renderers_)
    {
        renderer->remove(entity);
    }
}