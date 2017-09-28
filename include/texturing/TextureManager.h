//
// Created by Sp4rk on 22-08-17.
//

#ifndef CES_TEXTUREMANAGER_H
#define CES_TEXTUREMANAGER_H

#include <map>
#include <string>
#include <SDL_render.h>
#include <unordered_map>

// TODO: Add with sprite sheet cropping feature (Cf. Tutorial SDL, Lesson 11)
class TextureManager
{
public:
    TextureManager();

    ~TextureManager();

    void initWith(SDL_Renderer *renderer);

    bool add(std::string name, std::string path, SDL_Texture *texture = nullptr);

    void remove(const std::string &name);

    void clearAll();

    void close();

    size_t getTextureBankSize();

    static TextureManager *getInstance();

    SDL_Renderer *getRenderer();

    SDL_Texture *getTexture(const std::string &name);

private:

    static bool null(TextureManager *textureManager);
    SDL_Texture *createTexture(std::string path);

    SDL_Renderer *renderer_;

    const size_t INVALID_TEXTURE;

    static TextureManager *Instance; // singleton member

    std::unordered_map<std::string, std::string> mapNameToPath_;

    std::unordered_map<std::string, SDL_Texture *> textureBank_; // name / texture
};

#endif //CES_TEXTUREMANAGER_H
