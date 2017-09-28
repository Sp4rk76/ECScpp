//
// Created by Sp4rk on 14-08-17.
//

#ifndef CES_COMPONENTS_H
#define CES_COMPONENTS_H

#define MAX_ENTITIES 1000000 // with 10M entities, xFPS >> 60;

typedef enum
{
    NO_COMPONENT = 0,
    OBJECT2D = 1 << 1,
    SPRITE = 1 << 2, // Sprite = Texture + Size
    PLAYER = 1 << 3,
    PHYSICS2D = 1 << 4,
    BOXCOLLIDER2D = 1 << 5,
    CIRCLECOLLIDER2D = 1 << 6,
} Components;

#endif //CES_COMPONENTS_H
