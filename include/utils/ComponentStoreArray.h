//
// Created by Sp4rk on 16-09-17.
//

#ifndef CES_COMPONENTSTOREARRAY_H
#define CES_COMPONENTSTOREARRAY_H

#include <iostream>
#include <unordered_map>
#include <components/Components.h>

template<class T>
class ComponentStoreArray
{
public:
    explicit ComponentStoreArray(std::size_t size)
    {
        size_ = size > 0 ? size : MAX_ENTITIES;
        store_ = new T[size];
    }

    bool isInArrayRange(size_t entityID)
    {
        return entityID > size_ || entityID < 1;
    }

    void addComponent(size_t entityID, T &component)
    {
        if(isInArrayRange(entityID))
        {
            std::cout << "Error: entityID is out of range of the array" << std::endl;
        }
        else
        {
            store_[entityID] = component;
        }
    }

    T& get(size_t entityID)
    {
        return store_[entityID];
    }

    void removeComponent(size_t entityID)
    {
        if(isInArrayRange(entityID))
        {
            // bullshit
            store_[entityID] = T();
        }
    }

    // NOTE: we admit that the store is not resized..
    size_t size()
    {
        return size_;
    }

private:
    T* store_;
    size_t size_;
};

#endif //CES_COMPONENTSTOREARRAY_H
