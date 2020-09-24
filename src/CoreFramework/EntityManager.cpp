#include "EntityManager.h"

EntityManager::EntityManager()
{
    for (ECSConstants::Entity entity = 0; entity < ECSConstants::MAX_ENTITIES; entity++)
    {
        AvailableEntities.push(entity);
    }
}

ECSConstants::Entity EntityManager::CreateEntity()
{
    //Check if more entities can be made.
    assert(UsedEntities < ECSConstants::MAX_ENTITIES && "Number of entities is greater than the max.");
    ECSConstants::Entity entity = AvailableEntities.front();
    AvailableEntities.pop();
    ++UsedEntities;

    return entity;
}

void EntityManager::DestroyEntity(ECSConstants::Entity entity)
{
    assert(entity < ECSConstants::MAX_ENTITIES && "Out of range");
    //bitset.reset() resets all bits to 0000...
    EntitySignatures[entity].reset();
    AvailableEntities.push(entity);
    --UsedEntities;
}

void EntityManager::SetEntitySignature(ECSConstants::Entity entity, ECSConstants::Signature signature)
{
    assert(entity < ECSConstants::MAX_ENTITIES && "Out of range");
    EntitySignatures[entity] = signature;
}

ECSConstants::Signature EntityManager::GetentitySignature(ECSConstants::Entity entity)
{
    assert(entity < ECSConstants::MAX_ENTITIES && "Out of range");
    return EntitySignatures[entity];
}