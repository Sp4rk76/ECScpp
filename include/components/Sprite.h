//
// Created by Sp4rk on 16-08-17.
//

#ifndef CES_SPRITE_H
#define CES_SPRITE_H

#include <SDL_render.h>
#include "Object2D.h"

struct Sprite : public Object2D
{
    SDL_Texture *texture = nullptr;
    int w = 32;
    int h = 32;
};

#endif //CES_SPRITE_H
