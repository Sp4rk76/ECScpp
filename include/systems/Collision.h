//
// Created by Sp4rk on 03-09-17.
//

#ifndef CES_COLLISION_H
#define CES_COLLISION_H

#include <components/BoxCollider2D.h>
#include <components/CircleCollider2D.h>
#include "components/Vector2D.h"
#include "components/Rigidbody2D.h"
#include "components/Direction.h"

class Collision
{
public:
    bool collideX(Collider2D &a, int sceneWidth);

    bool collideY(Collider2D &a, int sceneHeight);

    double depthX(Collider2D &a, int sceneWidth);

    double depthY(Collider2D &a, int sceneHeight);

    double distance(double a, double b);

    /// NOTE: AABB is checked without offset values because collider position has just been updated in Physics system
    bool checkAABB(BoxCollider2D &a, BoxCollider2D &b);

    bool collision(CircleCollider2D &c1, CircleCollider2D &c2);

    Direction getDirectionX(BoxCollider2D &a, BoxCollider2D &b);

    Direction getDirectionY(BoxCollider2D &a, BoxCollider2D &b);

private:
    Vector2D directions_[4] = {
            {0.0f,  1.0f}, // up
            {0.0f,  -1.0f},  // down
            {-1.0f, 0.0f}, // left
            {1.0f,  0.0f}, // right
    };
};

#endif //CES_COLLISION_H