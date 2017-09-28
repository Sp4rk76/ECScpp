//
// Created by Sp4rk on 15-09-17.
//

#include "systems/SpriteRenderer.h"
#include "Scene.h"
#include "Entity.h"

SpriteRenderer::SpriteRenderer(int mask, Scene *scene) : Renderer(mask, scene),
                                                         renderer_(scene_->getRenderer()),
                                                         object2D_(nullptr),
                                                         sprite_(nullptr),
                                                         boxCollider2D_(nullptr),
                                                         circleCollider2D_(nullptr)
{}

void SpriteRenderer::render()
{

    std::vector<Entity *> &entities = getMatchingEntities();

    for (Entity *entity : entities)
    {
        mask_ = scene_->maskStore_.get(entity->id);
        object2D_ = &scene_->componentBaseStore_.get(entity->id);
        boxCollider2D_ = &scene_->boxCollider2DStore_.get(entity->id);
        circleCollider2D_ = &scene_->circleCollider2DStore_.get(entity->id);
        sprite_ = &scene_->spriteStore_.get(entity->id);

        // Render the sprite
        SDL_Rect renderSprites = {(int) object2D_->transform.position.x, (int) object2D_->transform.position.y,
                                  sprite_->w, sprite_->h};
        SDL_RenderCopy(renderer_, sprite_->texture, nullptr, &renderSprites);

        // TODO: Separate collider rendering thanks to a new eponym system

        // Render the BoxCollider2D (ONLY if solid)
        if (((mask_ & BOXCOLLIDER2D) == BOXCOLLIDER2D) && boxCollider2D_->isVisible)
        {
            SDL_SetRenderDrawColor(renderer_, 0xFF, 0x00, 0x00, 0xFF);
            SDL_Rect renderCollider = {(int) boxCollider2D_->x, (int) boxCollider2D_->y, boxCollider2D_->w,
                                       boxCollider2D_->h};
            SDL_RenderDrawRect(renderer_, &renderCollider);

            // Let the center appear !
            SDL_SetRenderDrawColor(renderer_, 0x00, 0xFF, 0x00, 0xFF);
            SDL_Rect renderColliderCenter = {(int) boxCollider2D_->x + (boxCollider2D_->w / 2),
                                             (int) boxCollider2D_->y + (boxCollider2D_->h / 2), 2, 2};
            SDL_RenderFillRect(renderer_, &renderColliderCenter);
        }

        // TODO: Draw a circle with some library (or just your brain, lol !)
        // Render the BoxCollider2D (ONLY if solid)
        if (((mask_ & CIRCLECOLLIDER2D) == CIRCLECOLLIDER2D) && circleCollider2D_->isVisible)
        {
            SDL_SetRenderDrawColor(renderer_, 0xFF, 0x00, 0x00, 0xFF);
            SDL_Rect renderCollider = {(int) circleCollider2D_->x, (int) circleCollider2D_->y, circleCollider2D_->w,
                                       circleCollider2D_->h};
            SDL_RenderDrawRect(renderer_, &renderCollider);

            // Let the center appear !
            SDL_SetRenderDrawColor(renderer_, 0x00, 0xFF, 0x00, 0xFF);
            SDL_Rect renderColliderCenter = {(int) circleCollider2D_->x + (circleCollider2D_->w / 2),
                                             (int) circleCollider2D_->y + (circleCollider2D_->h / 2), 2, 2};
            SDL_RenderFillRect(renderer_, &renderColliderCenter);
        }

    }
}

SpriteRenderer::~SpriteRenderer()
{
    delete object2D_;
    delete sprite_;
    delete boxCollider2D_;
    delete circleCollider2D_;

    object2D_ = nullptr;
    sprite_ = nullptr;
    boxCollider2D_ = nullptr;
    circleCollider2D_ = nullptr;
}