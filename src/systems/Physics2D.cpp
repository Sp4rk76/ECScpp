//
// Created by Sp4rk on 15-09-17.
//

#include "systems/Physics2D.h"
#include "Scene.h"
#include "Entity.h"

Physics::Physics(int mask, Scene *scene) : Updater(mask, scene),
                                           object2D_(nullptr),
                                           physics2D_(nullptr),
                                           boxCollider2D_(nullptr),
                                           circleCollider2D_(nullptr)
{}

void Physics::update()
{
    std::vector<Entity *> &entities = getMatchingEntities();

    for (Entity *entity : entities)
    {
        size_t entityId = entity->id;

        mask_ = scene_->maskStore_.get(entityId);
        object2D_ = &(scene_->componentBaseStore_.get(entityId));
        physics2D_ = &(scene_->rigidbody2DStore_.get(entityId));

        /// 1. Move x axis
        //  1.1 Update entity's x position
        object2D_->transform.position.x += physics2D_->velocity.x;

        //  1.2 Update entity's Rigidbody2D
        physics2D_->position.x = object2D_->transform.position.x;

        if (match(mask_, BOXCOLLIDER2D))
        {
            boxCollider2D_ = &(scene_->boxCollider2DStore_.get(entityId));
            boxCollider2D_->center.x = object2D_->transform.position.x + (object2D_->size.w / 2);
            boxCollider2D_->x = boxCollider2D_->center.x - (boxCollider2D_->w / 2) + boxCollider2D_->offsetX;

            if (collision_.collideX(*boxCollider2D_, scene_->getWidth()))
            {
                double depth = collision_.depthX(*boxCollider2D_, scene_->getWidth());
                object2D_->transform.position.x -= depth;
                boxCollider2D_->x -= depth;
            }
        }

        if (match(mask_, CIRCLECOLLIDER2D))
        {
            circleCollider2D_ = &(scene_->circleCollider2DStore_.get(entityId));
            circleCollider2D_->center.x = object2D_->transform.position.x + (object2D_->size.w / 2);
            circleCollider2D_->x =
                    circleCollider2D_->center.x - (circleCollider2D_->w / 2) + circleCollider2D_->offsetX;

            if (collision_.collideX(*circleCollider2D_, scene_->getWidth()))
            {
                double depth = collision_.depthX(*circleCollider2D_, scene_->getWidth());
                object2D_->transform.position.x -= depth;
                circleCollider2D_->x -= depth;
            }
        }

        // 2.2 Objects
        for (Entity *other : entities)
        {
            size_t otherId = other->id;

            if (otherId == entityId)
            {
                continue;
            }

            /// BOX <-> BOX (x-axis)
            if ((match(mask_, BOXCOLLIDER2D))
                && (match(scene_->maskStore_.get(otherId), BOXCOLLIDER2D)))
            {
                bool collideAABB = collision_.checkAABB(*boxCollider2D_, scene_->boxCollider2DStore_.get(otherId));

                if (collideAABB)
                {
                    // direction belongs to B, 'cause
                    Direction directionX = collision_.getDirectionX(*boxCollider2D_,
                                                                    scene_->boxCollider2DStore_.get(otherId));
                    double penetrationRight =
                            boxCollider2D_->x + boxCollider2D_->w - scene_->boxCollider2DStore_.get(otherId).x;
                    double penetrationLeft =
                            scene_->boxCollider2DStore_.get(otherId).x + scene_->boxCollider2DStore_.get(otherId).w -
                            boxCollider2D_->x;

                    if (directionX == LEFT)
                    {
                        object2D_->transform.position.x += penetrationLeft;
                        boxCollider2D_->x += penetrationLeft;
                    }

                    if (directionX == RIGHT)
                    {
                        object2D_->transform.position.x -= penetrationRight;
                        boxCollider2D_->x -= penetrationRight;
                    }
                }
            }

            /// CIRCLE <-> CIRCLE (x-axis)
            if ((match(mask_, CIRCLECOLLIDER2D))
                && (match(scene_->maskStore_.get(otherId), CIRCLECOLLIDER2D)))
            {
                bool collide = collision_.collision(*circleCollider2D_, scene_->circleCollider2DStore_.get(otherId));
                if (collide)
                {
                    // TODO: resolve circle-circle collision
                    cout << "Circle Collision, between " << entityId << " and " << otherId << endl;

                }
            }

            /// BOX <-> CIRCLE || CIRCLE <-> BOX
        }

        /// 3. Move y axis
        //  3.1 Update entity's x position
        object2D_->transform.position.y += physics2D_->velocity.y;
        //  3.2 Update entity's Rigidbody2D
        physics2D_->position.y = object2D_->transform.position.y;

        /// 4. Update 2D colliders' y & Check y collisions
        // 4.1 World
        if (match(mask_, BOXCOLLIDER2D))
        {
            boxCollider2D_->center.y = object2D_->transform.position.y + (object2D_->size.h / 2);
            boxCollider2D_->y = boxCollider2D_->center.y - (boxCollider2D_->h / 2) + boxCollider2D_->offsetY;
            if (collision_.collideY(*boxCollider2D_, scene_->getHeight()))
            {
                double depth = collision_.depthY(*boxCollider2D_, scene_->getHeight());
                object2D_->transform.position.y -= depth;
                boxCollider2D_->y -= depth;

                if (!match(mask_, PLAYER))
                {
                    physics2D_->velocity.y *= -1;
                }
            }
        }

        if (match(mask_, CIRCLECOLLIDER2D))
        {
            circleCollider2D_->center.y = object2D_->transform.position.y + (object2D_->size.h / 2);
            circleCollider2D_->y =
                    circleCollider2D_->center.y - (circleCollider2D_->h / 2) + circleCollider2D_->offsetY;
            if (collision_.collideY(*circleCollider2D_, scene_->getHeight()))
            {
                double depth = collision_.depthY(*circleCollider2D_, scene_->getHeight());
                object2D_->transform.position.y -= depth;
                circleCollider2D_->y -= depth;
            }
        }

        // 4.2 Objects
        for (Entity *other : entities)
        {
            size_t otherId = other->id;

            if (otherId == entityId)
            {
                continue;
            }

            /// BOX <-> BOX (x-axis)
            if ((match(mask_, BOXCOLLIDER2D))
                && (match(scene_->maskStore_.get(otherId), BOXCOLLIDER2D)))
            {
                bool collideAABB = collision_.checkAABB(*boxCollider2D_, scene_->boxCollider2DStore_.get(otherId));

                if (!collideAABB)
                {
                    continue;
                }

                Direction directionY = collision_.getDirectionY(*boxCollider2D_,
                                                                scene_->boxCollider2DStore_.get(otherId));
                double penetrationUp =
                        scene_->boxCollider2DStore_.get(otherId).y + scene_->boxCollider2DStore_.get(otherId).h -
                        boxCollider2D_->y;
                double penetrationDown =
                        boxCollider2D_->y + boxCollider2D_->h - scene_->boxCollider2DStore_.get(otherId).y;

                if (directionY == DOWN)
                {
                    object2D_->transform.position.y -= penetrationDown;
                    boxCollider2D_->y -= penetrationDown;
                }

                if (directionY == UP)
                {
                    object2D_->transform.position.y += penetrationUp;
                    boxCollider2D_->y += penetrationUp;
                }
            }


            /// CIRCLE <-> CIRCLE (x-axis)
            if ((match(mask_, CIRCLECOLLIDER2D))
                && (match(scene_->maskStore_.get(otherId), CIRCLECOLLIDER2D)))
            {

            }

            /// BOX <-> CIRCLE || CIRCLE <-> BOX
            if ((match(mask_, CIRCLECOLLIDER2D))
                && ((scene_->maskStore_.get(otherId) & CIRCLECOLLIDER2D)))
            {

            }
        }
    }
}

Physics::~Physics()
{
    delete object2D_;
    delete physics2D_;
    delete boxCollider2D_;
    delete circleCollider2D_;

    object2D_ = nullptr;
    physics2D_ = nullptr;
    boxCollider2D_ = nullptr;
    circleCollider2D_ = nullptr;
}
