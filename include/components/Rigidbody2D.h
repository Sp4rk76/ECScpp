//
// Created by Sp4rk on 24-08-17.
//

#ifndef CES_RIGIDBODY2D_H
#define CES_RIGIDBODY2D_H

#include "Vector2D.h"
#include "Object2D.h"
#include "Collider2D.h"

/// NOTE: RigidBody has no size, whereas Collider has one !
struct Rigidbody2D : public Object2D
{
    Vector2D position;
    Vector2D velocity;

    double cOM = 0; // center of mass

    /// NOTE: We suppose that the gravitational field is uniform
    /// so the center of gravity is the same as the center of mass
    double cOG = 0;
    const double g = 9.81;

    // bool gravity = 0;
    // double mass = 1;
};

#endif //CES_RIGIDBODY2D_H
