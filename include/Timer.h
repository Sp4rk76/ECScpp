//
// Created by Sp4rk on 22-08-17.
//

#ifndef CES_TIMER_H
#define CES_TIMER_H

#include <SDL_quit.h>

class Timer
{
public:
    Timer();

    void start();

    void stop();

    void pause();

    void unpause();

    // Get the Timer's time
    Uint32 getTicks();

    // Check the Timer's status
    bool isStarted();

    bool isPaused();

private:
    // Clock time when fpsTimer_ start
    Uint32 startTicks_;

    // Ticks stored when fpsTimer_ was paused
    Uint32 pausedTicks_;

    // Timer status
    bool started_;

    bool paused_;

};

#endif //CES_TIMER_H
