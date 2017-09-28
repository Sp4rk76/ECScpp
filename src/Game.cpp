//
// Created by Sp4rk on 16-08-17.
//

#include "Game.h"
#include "Scene.h"

bool Game::init()
{
    bool success = true;

    screen_ = new Screen("BindingWorlds", 1080, 720);
    if (!screen_->init())
    {
        cout << "Failed to initialize Screen" << endl;
        success = false;
    } else
    {
        scene_ = new Scene(this);
        if (!scene_->init())
        {
            cout << "Failed to initialize Scene" << endl;
            success = false;
        } else
        {
            if (!scene_->load())
            {
                cout << "Failed to load Scene (missing components)" << endl;
                success = false;
            }
        }
    }



    return success;
}

void Game::start()
{
    if (init())
    {
        scene_->run();
    }
}

Screen *Game::getScreen()
{
    return screen_;
}

void Game::stop()
{
    scene_->close();
    screen_->close();
    // TODO: close textureManager && close entityManager

    delete scene_;
    delete screen_;

    scene_ = nullptr;
    screen_ = nullptr;
}

Game::Game() : screen_(nullptr), scene_(nullptr) {}

Game::~Game()
{
    stop();
}
