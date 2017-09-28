//
// Created by Sp4rk on 03-09-17.
//

#ifndef CES_VECTOR2D_H
#define CES_VECTOR2D_H


struct Vector2D
{
    double x = 0;
    double y = 0;

    Vector2D() : x(0), y(0) {}

    Vector2D(double newX, double newY) : x(newX), y(newY) {}
};

#endif //CES_VECTOR2D_H
