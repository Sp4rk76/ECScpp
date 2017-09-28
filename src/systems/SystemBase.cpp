//
// Created by Sp4rk on 21-09-17.
//

#include "systems/SystemBase.h"
#include "Scene.h"

SystemBase::SystemBase(int mask, Scene *scene) : mask_(mask), scene_(scene), matchingEntities_()
{}

bool SystemBase::match(int entityMask, int requiredMask)
{
    return ((entityMask & requiredMask) == requiredMask);
}

void SystemBase::add(Entity *entity)
{
    auto entityMask = scene_->maskStore_.get(entity->id);
    if (!match(entityMask, mask_))
    {
        cout << "No matching system for this entity (" << entity->id << ") with mask " << entityMask << endl;
    }
    else
    {
        matchingEntities_.emplace_back(entity);
    }
}

void SystemBase::remove(Entity *entity)
{
    matchingEntities_.erase(std::remove(matchingEntities_.begin(), matchingEntities_.end(), entity),
                            matchingEntities_.end());
}

int SystemBase::getMask()
{
    return mask_;
}

Scene *SystemBase::getScene()
{
    if (scene_ == nullptr)
    {
        std::cout << "No scene attached !" << std::endl;
    }

    return scene_;
}

void SystemBase::setMask(int mask)
{
    if (mask_ != mask && mask > 0)
    {
        mask_ = mask;
    }
}

void SystemBase::setScene(Scene &scene)
{
    scene_ = &scene;
}

std::vector<Entity *> &SystemBase::getMatchingEntities()
{
    return matchingEntities_;
}

