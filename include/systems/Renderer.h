//
// Created by Sp4rk on 16-08-17.
//

#ifndef CES_RENDERER_H
#define CES_RENDERER_H

#include "SystemBase.h"

class Renderer : public SystemBase
{
public:
    Renderer(int mask, Scene *scene);

    virtual void render() = 0;
};

#endif //CES_RENDERER_H
