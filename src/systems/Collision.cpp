//
// Created by Sp4rk on 03-09-17.
//

#include <cmath>
#include <iostream>
#include <components/Rigidbody2D.h>
#include "systems/Collision.h"

bool Collision::collideX(Collider2D &a, int sceneWidth)
{
    // (rightA > sceneWidth) || (leftA < 0)
    return ((a.x + a.w > sceneWidth) || (a.x < 0));
}

bool Collision::collideY(Collider2D &a, int sceneHeight)
{
    // (bottomA > sceneHeight) || topA < 0
    return ((a.y + a.h > sceneHeight) || (a.y < 0));
}

double Collision::depthX(Collider2D &a, int sceneWidth)
{
    if (a.x + a.w > sceneWidth) // out by right
    {
        return distance((a.x + a.w), sceneWidth);
    }
    if (a.x < 0)
    {
        // negative to be able to apply substract operation to both
        return -distance(a.x, 0);
    }

}

double Collision::depthY(Collider2D &a, int sceneHeight)
{
    if (a.y + a.h > sceneHeight)
    {
        return distance((a.y + a.h), sceneHeight);
    }
    if (a.y < 0)
    {
        return -distance(a.y, 0);
    }
}

double Collision::distance(double a, double b)
{
    return sqrt((a - b) * (a - b));
}

bool Collision::checkAABB(BoxCollider2D &a, BoxCollider2D &b)
{
    double topA = a.y;
    double bottomA = a.y + a.h;
    double leftA = a.x;
    double rightA = a.x + a.w;

    double topB = b.y;
    double bottomB = b.y + b.h;
    double leftB = b.x;
    double rightB = b.x + b.w;

    if (topA >= bottomB)
    { return false; }
    else if (bottomA <= topB)
    { return false; }
    else if (leftA >= rightB)
    { return false; }
    else if (rightA <= leftB)
    { return false; }

    return true;
}

bool Collision::collision(CircleCollider2D &C1, CircleCollider2D &C2)
{
    double distance = (C1.center.x - C2.center.x) * (C1.center.x - C2.center.x) +
                      (C1.center.y - C2.center.y) * (C1.center.y - C2.center.y);
    double distanceMin = (C1.radius + C2.radius) * (C1.radius + C2.radius);
    return distance <= distanceMin;
}

Direction Collision::getDirectionX(BoxCollider2D &a, BoxCollider2D &b)
{
    double topA = a.y;
    double bottomA = a.y + a.h;
    double leftA = a.x;
    double rightA = a.x + a.w;

    double topB = b.y;
    double bottomB = b.y + b.h;
    double leftB = b.x;
    double rightB = b.x + b.w;

    if (bottomA > topB && topA < bottomB)
    {
        if (leftA < rightB && leftA > leftB)
        {
            return LEFT;
        }
        else
        {
            return RIGHT;
        }
    }
}

Direction Collision::getDirectionY(BoxCollider2D &a, BoxCollider2D &b)
{
    double topA = a.y;
    double bottomA = a.y + a.h;
    double leftA = a.x;
    double rightA = a.x + a.w;

    double topB = b.y;
    double bottomB = b.y + b.h;
    double leftB = b.x;
    double rightB = b.x + b.w;

    if (leftA < rightB && rightA > leftB)
    {
        if (topA < bottomB && topA > topB)
        {
            return UP;
        }
        else
        {
            return DOWN;
        }
    }
}
