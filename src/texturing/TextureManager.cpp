//
// Created by Sp4rk on 22-08-17.
//

#include <iostream>
#include <SDL_image.h>
#include "texturing/TextureManager.h"

TextureManager *TextureManager::Instance = nullptr;

TextureManager::TextureManager() : INVALID_TEXTURE(0), renderer_(nullptr)
{
    mapNameToPath_.insert(std::pair<std::string, std::string>("-", "-"));
    textureBank_.insert(std::pair<std::string, SDL_Texture *>("-", nullptr));
}

void TextureManager::initWith(SDL_Renderer *renderer)
{
    if (renderer == nullptr)
    {
        std::cout << "Warning: NULL parameter" << std::endl;
    }

    renderer_ = renderer;
}

bool TextureManager::null(TextureManager *textureManager)
{
    return textureManager == nullptr;
}

// TODO: See if this function can return a "nullptr" when "path" is not valid
SDL_Texture *TextureManager::createTexture(std::string path)
{
    std::cout << "Texture Path => " << path << std::endl;

    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load image at " << path << ". IMG Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        if (renderer_ == nullptr)
        {
            std::cout << "Error: texture renderer not initialized" << std::endl;
        }
        else
        {
            // Create a texture from surface's pixels
            newTexture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
            if (newTexture == nullptr)
            {
                std::cout << "Unable to optimize image localized at " << path << ". SDL Error: " << SDL_GetError()
                          << std::endl;
            }
        }

        // Free "old" surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool TextureManager::add(std::string name, std::string path, SDL_Texture *texture)
{
    bool success = true;

    if (mapNameToPath_.count(name) > 0)
    {
        std::cout << "Error: a texture is already registered under the name '" << name << "'" << std::endl;
        success = false;
    }
    else
    {
        if (texture == nullptr)
        {
            texture = createTexture(path);
            if (texture == nullptr)
            {
                std::cout << "Failed to load texture at specified path: " << path.c_str() << std::endl;
                success = false;
            }
            else
            {
                mapNameToPath_.insert(std::pair<std::string, std::string>(name, path));
                textureBank_.insert(std::pair<std::string, SDL_Texture *>(name, texture));
            }
        }
    }

    return success;
}

void TextureManager::remove(const std::string &name)
{
    if (mapNameToPath_.count(name) <= 0)
    {
        std::cout << "Error: Cannot remove name '" << name << "' which does not exist" << std::endl;
    }
    else
    {
        mapNameToPath_.erase(name);
        textureBank_.erase(name);
    }
}

//TODO: see how to clear map of pointers !
void TextureManager::clearAll()
{
    mapNameToPath_.clear();
    textureBank_.clear();
}

void TextureManager::close()
{
    if (!null(TextureManager::Instance))
    {
        std::cout << "CLose !" << std::endl;

        clearAll();

        SDL_DestroyRenderer(renderer_);

        delete Instance;

        Instance = nullptr;
    }
}

TextureManager *TextureManager::getInstance()
{
    if (null(Instance))
    {
        return Instance = new TextureManager();
    }
    return Instance;
}

SDL_Renderer *TextureManager::getRenderer()
{
    return renderer_;
}

size_t TextureManager::getTextureBankSize()
{
    return (textureBank_.size() - 1);
}

SDL_Texture *TextureManager::getTexture(const std::string &name)
{
    if (textureBank_.count(name) < 0)
    {
        std::cout << "Error: Name '" << name << "' is not registered in bank" << std::endl;
        return nullptr;
    }

    return textureBank_[name];
}

TextureManager::~TextureManager()
{

}



