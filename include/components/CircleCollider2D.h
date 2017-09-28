//
// Created by Sp4rk on 14-09-17.
//

#ifndef CES_CIRCLECOLLIDER2D_H
#define CES_CIRCLECOLLIDER2D_H

#include "Collider2D.h"

struct CircleCollider2D : public Collider2D
{
    int radius = w > 0 ? w / 2 : 32;
};

#endif //CES_CIRCLECOLLIDER2D_H
