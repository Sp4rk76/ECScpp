//
// Created by Sp4rk on 10-08-17.
//

#ifndef CES_IGAME_H
#define CES_IGAME_H

#include "display/Screen.h"

class IGame
{
public:
    virtual Screen *getScreen() = 0;

    virtual ~IGame() {};
};

#endif //CES_IGAME_H
