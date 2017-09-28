//
// Created by Sp4rk on 08-08-17.
//

#ifndef CES_SCENE_H
#define CES_SCENE_H

#include <SDL_image.h>
#include <vector>
#include <algorithm>

#include <components/Components.h>
#include <components/Sprite.h>
#include <components/Rigidbody2D.h>
#include <components/BoxCollider2D.h>
#include <components/CircleCollider2D.h>

#include "Timer.h"

#include <utils/ComponentStore.h>

#include "Entity.h"
#include "EntityManagerOld.h"
#include <systems/Renderer.h>
#include <systems/Updater.h>

#include "IGame.h"

using namespace std;

class Scene
{
public:
    Scene(IGame *game);

    bool init();

    bool load();

    size_t loadTextures();

    size_t loadComponents();

    size_t loadUpdaters();

    size_t loadRenderers();

    void run();

    void handle(SDL_Event &event);

    void update();

    void calculateFPS();

    void render();

    void capFPS(int cap = 60);

    unsigned int hasPlayer();

    void resetPlayer(unsigned int player);

    void close();

    vector<Updater *> updaters_;

    vector<Renderer *> renderers_;

    ComponentStore<int> maskStore_;

    ComponentStore<Object2D> componentBaseStore_;

    ComponentStore<Rigidbody2D> rigidbody2DStore_;

    ComponentStore<BoxCollider2D> boxCollider2DStore_;

    ComponentStore<CircleCollider2D> circleCollider2DStore_;

    ComponentStore<Sprite> spriteStore_;

    int getWidth();

    int getHeight();

    IGame *getGame();

    SDL_Renderer *getRenderer();

    void setWidth(int width);

    void setHeight(int height);

private:
    int width_;

    int height_;

    bool quit_;

    IGame *game_;

    SDL_Renderer *renderer_;

    Timer fpsTimer_;

    Timer capTimer_;

    size_t countedFrames_;

    EntityManagerOld* entityManager_;

};

#endif //CES_SCENE_H