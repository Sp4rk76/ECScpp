//
// Created by Sp4rk on 16-08-17.
//

#ifndef CES_SPRITERENDERER_H
#define CES_SPRITERENDERER_H

#include <algorithm>
#include <SDL_render.h>
#include <components/BoxCollider2D.h>
#include <components/CircleCollider2D.h>
#include <components/Sprite.h>
#include "Renderer.h"

class SpriteRenderer : public Renderer
{
public:
    SpriteRenderer(int mask, Scene *scene);

    void render() override;

    ~SpriteRenderer();

private:
    SDL_Renderer *renderer_;
    Object2D* object2D_;
    Sprite* sprite_;
    BoxCollider2D* boxCollider2D_;
    CircleCollider2D* circleCollider2D_;
};

#endif //CES_SPRITERENDERER_H
