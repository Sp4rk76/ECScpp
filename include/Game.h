//
// Created by Sp4rk on 09-08-17.
//

#ifndef CES_GAMEVIEW_H
#define CES_GAMEVIEW_H

#include "IGame.h"

class Scene;

/*
 * The GAME class :
 *      -> start/init/run/stop whole game
 *      -> create the Screen (=> screen/window)
 *      -> create and load a Scene (=> world)
 */
class Game : public IGame
{
public:
    Game();

    ~Game() override;

    bool init();

    void start();

    void stop();

    Screen *getScreen() override;

private:
    Screen *screen_;
    Scene *scene_;
};

#endif //CES_GAMEVIEW_H
