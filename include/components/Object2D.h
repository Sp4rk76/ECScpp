//
// Created by Sp4rk on 09-09-17.
//

#ifndef CES_COMPONENT_H
#define CES_COMPONENT_H

#include "Transform.h"
#include "Size.h"

struct Object2D
{
    int entityId = 0;
    Transform transform;
    Size size;
};

#endif //CES_COMPONENT_H
