//
// Created by Sp4rk on 09-09-17.
//

#ifndef CES_COLLIDER2D_H
#define CES_COLLIDER2D_H

#include "Object2D.h"

struct Collider2D : public Object2D
{
    double x = 0;
    double y = 0;
    int w = 32;
    int h = 32;
    int offsetX = 0;
    int offsetY = 0;
    bool isVisible = true;
    Vector2D center = {x + (w/2), y + (h/2)};
};

#endif //CES_COLLIDER2D_H
