#pragma once

#include <memory>

#include "ECSConstants.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

class EntityComponentSystemInterface//Name pending
{
private:
    std::unique_ptr<ComponentManager> ComponentManagerPtr;
    std::unique_ptr<EntityManager> EntityManagerPtr;
    std::unique_ptr<SystemManager> SystemManagerPtr;
public:
    void Init();//should be constructor?

    ECSConstants::Entity CreateEntity();

    void DestroyEntity(ECSConstants::Entity entity);

    template <typename T>
    void RegisterComponent()
    {
        ComponentManagerPtr->RegisterComponent<T>();
    }

    template <typename T>
    void AddComponent(ECSConstants::Entity entity, T component)
    {
        ComponentManagerPtr->AddComponent<T>(entity, component);

        auto signature = EntityManagerPtr->GetentitySignature(entity);
        signature.set(ComponentManagerPtr->GetComponentType<T>(), true);
        EntityManagerPtr->SetEntitySignature(entity, signature);
        SystemManagerPtr->EntitySignatureChanged(entity, signature);
    }

    template <typename T>
    void RemoveComponent(ECSConstants::Entity entity)
    {
        ComponentManagerPtr->RemoveComponent(entity);

        auto signature = EntityManagerPtr->GetentitySignature(entity);
        signature.set(ComponentManagerPtr->GetComponentType<T>(), false);
        EntityManagerPtr->SetEntitySignature(entity, signature);
        SystemManagerPtr->EntitySignatureChanged(entity, signature);
    }

    template <typename T>
    T& GetComponent(ECSConstants::Entity entity)
    {
        return ComponentManagerPtr->GetComponent<T>(entity);
    }

    template <typename T>
    ECSConstants::ComponentType GetComponentType()
    {
        return ComponentManagerPtr->GetComponentType<T>();
    }

    template <typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        return SystemManagerPtr->RegisterSystem<T>();
    }

    template <typename T>
    void SetSystemSignature(ECSConstants::Signature signature)
    {
        SystemManagerPtr->SetSignature<T>(signature);
    }
};