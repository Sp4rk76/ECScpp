//
// Created by Sp4rk on 16-08-17.
//

#ifndef CES_PHYSICS2D_H
#define CES_PHYSICS2D_H

#include <components/Rigidbody2D.h>
#include "Updater.h"
#include "Collision.h"

class Physics : public Updater
{
public:
    Physics(int mask, Scene *scene);

    void update() override;

    ~Physics();

private:
    Collision collision_;
    Object2D *object2D_;
    Rigidbody2D *physics2D_;
    BoxCollider2D *boxCollider2D_;
    CircleCollider2D *circleCollider2D_;
};

#endif //CES_PHYSICS2D_H
