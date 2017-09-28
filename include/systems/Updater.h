//
// Created by Sp4rk on 11-08-17.
//

#ifndef CES_UPDATER_H
#define CES_UPDATER_H

#include "SystemBase.h"

class Updater : public SystemBase
{
public:
    Updater(int mask, Scene *scene);

    virtual void update() = 0;
};

#endif //CES_UPDATER_H
