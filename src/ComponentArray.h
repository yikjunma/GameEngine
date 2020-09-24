#pragma once
#include <cassert>
#include <array>
#include <unordered_map>

#include "IComponentArray.h"

template<typename T>
class ComponentArray : public IComponentArray
{
private:
    std::array<T, ECSConstants::MAX_ENTITIES> _ComponentArray;
    std::unordered_map<ECSConstants::Entity, size_t> EntityToIndexMap;
    std::unordered_map<size_t, ECSConstants::Entity> IndexToEntityMap;
    size_t Size;

public:
    void InsertComponent(ECSConstants::Entity entity, T component)
    {
        assert(EntityToIndexMap.find(entity) == EntityToIndexMap.end() && "Component duplication");

        size_t tempIndex = Size;
        EntityToIndexMap[entity] = tempIndex;
        IndexToEntityMap[tempIndex] = entity;
        _ComponentArray[tempIndex] = component;
        ++Size;
    }

    void RemoveComponent(ECSConstants::Entity entity)
    {
        assert(EntityToIndexMap.find(entity) != EntityToIndexMap.end() && "Attempt to remove non-existing component");

        size_t removeIndex = EntityToIndexMap[entity];
        size_t lastIndex = Size - 1;
        _ComponentArray[removeIndex] = _ComponentArray[lastIndex];

        ECSConstants::Entity EntityInLastElement = IndexToEntityMap[lastIndex];
        EntityToIndexMap[EntityInLastElement] = removeIndex;
        IndexToEntityMap[removeIndex] = EntityInLastElement;

        EntityToIndexMap.erase(entity);
        IndexToEntityMap.erase(lastIndex);

        --Size;
    }

    T& GetComponent(ECSConstants::Entity entity)
    {
        assert(EntityToIndexMap.find(entity) != EntityToIndexMap.end());
        return _ComponentArray[EntityToIndexMap[entity]];
    }

    void EntityDestroyed(ECSConstants::Entity entity) override
    {
        if (EntityToIndexMap.find(entity) != EntityToIndexMap.end())
        {
            RemoveComponent(entity);
        }
    }
};