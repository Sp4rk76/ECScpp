//
// Created by Sp4rk on 16-08-17.
//

#include "Scene.h"
#include <systems/Physics2D.h>
#include "systems/SpriteRenderer.h"

Scene::Scene(IGame *game)
{
    width_ = 0;
    height_ = 0;
    game_ = game;
    quit_ = false;
    countedFrames_ = 0;
    entityManager_ = nullptr;
}

bool Scene::init()
{
    bool success = true;

    SDL_Window *window = (game_->getScreen()->getWindow());

    if (window == NULL)
    {
        std::cout << "Rendered can not be initialized when there is no window (window == NULL)" << std::endl;
    }
    else
    {
        // Create renderer for the window
        renderer_ = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer_ == nullptr)
        {
            std::cout << "Failed to create Renderer " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            // Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cout << "Failed to initialize SDL Image " << IMG_GetError() << std::endl;
                success = false;
            }
            else
            {
                TextureManager::getInstance()->initWith(renderer_);
                entityManager_ = new EntityManagerOld(*this);
            }
        }
    }

    return success;
}

bool Scene::load()
{
    bool success = true;

    size_t loadedUpdaters = loadUpdaters();
    size_t loadedRenderers = loadRenderers();
    size_t loadedTextures = loadTextures();
    size_t loadedComponents = loadComponents();

    std::cout << "Loaded Updaters: " << loadedUpdaters << std::endl;
    std::cout << "Loaded Renderers: " << loadedRenderers << std::endl;
    std::cout << "Loaded Textures: " << loadedTextures << std::endl;
    std::cout << "Loaded Components: " << loadedComponents << std::endl;

    if (loadedUpdaters == 0)
    {
        std::cout << "No components loaded" << std::endl;
    }

    if (loadedRenderers == 0)
    {
        std::cout << "No renderers loaded" << std::endl;
    }

    if (loadedComponents == 0)
    {
        std::cout << "No components loaded" << std::endl;
    }

    /// TMP !
    auto entityManager_ = new EntityManagerOld(*this);
    SDL_Window *window = getGame()->getScreen()->getWindow();
    entityManager_->createBall(350, (SDL_GetWindowSurface(window)->h / 2) - 16);
    entityManager_->createBall(450, (SDL_GetWindowSurface(window)->h / 2) - 16);
    entityManager_->createPlayer(450, (SDL_GetWindowSurface(window)->h / 2) - 16 + 300);
    ///

    return success;
}

size_t Scene::loadTextures()
{
    TextureManager::getInstance()->add("none", "D:\\resources\\foo.png");
    TextureManager::getInstance()->add("player", "D:\\resources\\boss.png");
    TextureManager::getInstance()->add("ball", "D:\\resources\\ball.png");
    TextureManager::getInstance()->add("background", "D:\\resources\\background.png");

    return (TextureManager::getInstance()->getTextureBankSize());
}

size_t Scene::loadComponents()
{
    int loadedComponents = 0;

    // TODO: load JSON components with a JSONLoader class
    // TODO: JSONLoader.load(entity);

    return loadedComponents;
}

size_t Scene::loadUpdaters()
{
    updaters_ = {new Physics(OBJECT2D | PHYSICS2D, this)};
    return updaters_.size();
}

size_t Scene::loadRenderers()
{
    renderers_ = {new SpriteRenderer(OBJECT2D | SPRITE, this)};
    return renderers_.size();
}

void Scene::run()
{
    SDL_Event event;

    countedFrames_ = 0;
    fpsTimer_.start();

    while (!quit_)
    {

        capTimer_.start();

        handle(event);

        update();

        calculateFPS();

        render();

        ++countedFrames_;
        capFPS(12000);
    }

    close();
}

void Scene::handle(SDL_Event &event)
{
    unsigned int player = this->hasPlayer();

    // Handle events on queue
    while (SDL_PollEvent(&event) != 0)
    {
        //User requests quit_
        if (event.type == SDL_QUIT && event.key.repeat == 0)
        {
            quit_ = true;
        }

        //Player not exists
        if (!player)
        {
            return;
        }

        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    rigidbody2DStore_.get(player).velocity.y -= 1;
                    break;
                case SDLK_DOWN:
                    rigidbody2DStore_.get(player).velocity.y += 1;
                    break;
                case SDLK_LEFT:
                    rigidbody2DStore_.get(player).velocity.x -= 1;
                    break;
                case SDLK_RIGHT:
                    rigidbody2DStore_.get(player).velocity.x += 1;
                    break;
                case SDLK_r:
                    resetPlayer(player);
                default:
                    std::cout << "No match for this key pressed !" << std::endl;
                    break;
            }
        }
        if (event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    rigidbody2DStore_.get(player).velocity.y += 1;
                    break;
                case SDLK_DOWN:
                    rigidbody2DStore_.get(player).velocity.y -= 1;
                    break;
                case SDLK_LEFT:
                    rigidbody2DStore_.get(player).velocity.x += 1;
                    break;
                case SDLK_RIGHT:
                    rigidbody2DStore_.get(player).velocity.x -= 1;
                    break;
                default:
                    std::cout << "No match for this key released !" << std::endl;
                    break;
            }
        }
    }
}

void Scene::update()
{
    for (Updater *updater : updaters_)
    {
        updater->update(/*(Uint32) (fpsTimer_.getTicks() / 1000.f)*/);
        std::cout << "Updater size = " << updater->getMatchingEntities().size() << std::endl;
    }
}

void Scene::render()
{
    // CLEAR screen
    SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer_);

    // RENDER screen
    for (Renderer *renderer : renderers_)
    {
        renderer->render();
        std::cout << "Renderer size = " << renderer->getMatchingEntities().size() << std::endl;
    }

    // UPDATE screen rendering
    SDL_RenderPresent(renderer_);
}

unsigned int Scene::hasPlayer()
{
    for (unsigned int index = 1; index <= maskStore_.size(); index++)
    {
        if ((maskStore_.get(index) & PLAYER) == PLAYER)
        {
            return index;
        }
    }
    return 0;
}

void Scene::calculateFPS()
{
    float avgFPS = countedFrames_ / (fpsTimer_.getTicks() / 1000.f);

    if (avgFPS > 2000000)
    {
        avgFPS = -1;
    }

    std::cout << "FPS: " << avgFPS << std::endl;
}

void Scene::capFPS(int cap)
{
    //If frame finished early
    int frameTicks = capTimer_.getTicks();
    if (frameTicks < (1000 / cap))
    {
        //Wait remaining time
        SDL_Delay((Uint32) ((1000 / cap) - frameTicks));
    }
}

void Scene::close()
{
    // Destroy SDL objects
//     SDL_DestroyRenderer(renderer_);

    // Delete some pointers
    //delete game_;
    //game_ = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer *Scene::getRenderer()
{
    return renderer_;
}

IGame *Scene::getGame()
{
    return game_;
}

void Scene::resetPlayer(unsigned int player)
{
    componentBaseStore_.get(player).transform.position.x = 0;
    componentBaseStore_.get(player).transform.position.y = 0;
}

int Scene::getWidth()
{
    if (width_ <= 0)
    {
        return game_->getScreen()->getWidth();
    }

    return width_;
}

int Scene::getHeight()
{
    if (height_ <= 0)
    {
        return game_->getScreen()->getHeight();
    }

    return height_;
}

void Scene::setWidth(int width)
{
    if (width <= 0)
    {
        std::cout << "Error: width value is out of range." << std::endl;
    }
    else
    {
        width_ = width;
    }
}

void Scene::setHeight(int height)
{
    if (height <= 0)
    {
        std::cout << "Error: height value is out of range." << std::endl;
    }
    else
    {
        height_ = height;
    }
}
