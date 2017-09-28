//
// Created by Sp4rk on 16-09-17.
//

#ifndef CES_COMPONENTSTORE_H
#define CES_COMPONENTSTORE_H

#include <vector>
#include <unordered_map>
#include <components/Object2D.h>
#include <iostream>

template<class T>
class ComponentStore
{
public:
//    ComponentStore(const ComponentStore &world) = delete;
//
//    ComponentStore(ComponentStore &&world) = delete;
//
//    ComponentStore &operator=(const ComponentStore &) = delete;
//
//    ComponentStore &operator=(ComponentStore &&) = delete;
//
//    ComponentStore();
//
//    ComponentStore(std::size_t size);
//
//    ~ComponentStore();

    bool isValid(int entityID)
    {
        return entityID != 0;
    }

    void addComponent(int entityID, T &/*&*/ component)
    {
        if (!isValid(entityID))
        {
            std::cout << "..." << std::endl;
        }
        else
        {
            store_.push_back(component);

            int storeID = store_.size() - 1;

            /// TODO: check if entityID is free !
            if (storeMap_.count(entityID) > 0)
            {
                std::cout << "Error: Can not have more than one component of the same type for this entity."
                          << std::endl;
            }
            else
            {

            }
            storeMap_.insert(std::make_pair(entityID, storeID));
        }
    }

    void removeComponent(int entityID)
    {
        /// entity | entityStoreID(not needed)
        /// 5 | 0
        /// lastEntityID | lastEntityStoreID
        /// 7 | 1

        /// We want the following result
        /// x [ x
        /// 7 | 0
        /// => lastEntityID | entityStoreID

        int entityStoreID = storeMap_[entityID];

        int lastEntityStoreID = store_.size() - 1;
        int lastEntityID = store_[lastEntityStoreID].entityId;

        // Put entity to delete at the end
        std::swap(store_[entityStoreID], store_.back());

        // Update map for modified component
        storeMap_[lastEntityID] = entityStoreID;

        // Erase entity from both
        store_.pop_back();
        storeMap_.erase(entityID);
    }

    std::vector<T> getAll()
    {
        return store_;
    }

    std::unordered_map<int, int> getMap()
    {
        return storeMap_;
    }

    T& get(std::size_t entity)
    {
        return store_[storeMap_.at(entity)];
    }

    std::size_t size()
    {
        return store_.size();
    }

    void clear()
    {
        store_.clear();
    }

    std::vector<T> store_;
    std::unordered_map<int, int> storeMap_;

};

#endif //CES_COMPONENTSTORE_H
