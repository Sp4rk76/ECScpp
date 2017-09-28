//
// Created by Sp4rk on 22-08-17.
//

#include <SDL_timer.h>
#include "Timer.h"

Timer::Timer()
{
    startTicks_ = 0;
    pausedTicks_ = 0;
    started_ = false;
    paused_ = false;
}

void Timer::start()
{
    started_ = true;
    paused_ = false;
    // Get current clock time
    startTicks_ = SDL_GetTicks();
    pausedTicks_ = 0;
}

void Timer::stop()
{
    started_ = false;
    paused_ = false;
    // Reset all ticks
    startTicks_ = 0;
    pausedTicks_ = 0;
}

void Timer::pause()
{

    if (started_ && !paused_)
    {
        paused_ = true;

        // Calculate pause ticks (current time)
        pausedTicks_ = SDL_GetTicks() - startTicks_;
        // Reset start ticks
        startTicks_ = 0;
    }
}

void Timer::unpause()
{
    if (started_ && paused_)
    {
        paused_ = false;

        // Calculate start ticks (current time)
        startTicks_ = SDL_GetTicks() - pausedTicks_;
        // Reset paused ticks
        pausedTicks_ = 0;
    }
}

Uint32 Timer::getTicks()
{
    // Current time
    Uint32 currentTime = 0;

    if (started_)
    {
        if (paused_)
        {
            currentTime = pausedTicks_;
        } else
        {
            currentTime = SDL_GetTicks() - startTicks_;
        }
    }

    return currentTime;
}

bool Timer::isStarted()
{
    return started_;
}

bool Timer::isPaused()
{
    return started_ && paused_;
}

