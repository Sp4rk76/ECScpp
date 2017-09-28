//
// Created by Sp4rk on 28-09-17.
//

#ifndef ECSCPP_INSTANCEDATA_H
#define ECSCPP_INSTANCEDATA_H

#include "Vector3.h"
#include "Entity.h"

struct InstanceData
{
    unsigned size; ///< Number of used instances
    unsigned capacity; ///< Number of allocated instances
    void *buffer; ///< Buffer with instance data

    Entity *entity;
    float *mass;
    Vector3 *position;
    Vector3 *velocity;
    Vector3 *acceleration;
};

#endif //ECSCPP_INSTANCEDATA_H
