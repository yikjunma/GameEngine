#include "EntityComponentSystemInterface.h"

void EntityComponentSystemInterface::Init()//should be constructor?
{
    ComponentManagerPtr = std::make_unique<ComponentManager>();
    EntityManagerPtr = std::make_unique<EntityManager>();
    SystemManagerPtr = std::make_unique<SystemManager>();
}

ECSConstants::Entity EntityComponentSystemInterface::CreateEntity()
{
    return EntityManagerPtr->CreateEntity();
}

void EntityComponentSystemInterface::DestroyEntity(ECSConstants::Entity entity)
{
    EntityManagerPtr->DestroyEntity(entity);
    ComponentManagerPtr->EntityDestroyed(entity);
    SystemManagerPtr->EntityDestroyed(entity);
}