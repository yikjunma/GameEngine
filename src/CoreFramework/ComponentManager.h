#pragma once
#include <unordered_map>
#include <memory>
#include <any>
#include <typeinfo>

#include "ECSConstants.h"
#include "componentArray.h"

class ComponentManager
{//implement self registration for components latter.
private:
    std::unordered_map<const char*, ECSConstants::ComponentType> ComponentTypes{};
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> ComponentArrays{};
    ECSConstants::ComponentType NextComponentType{};

    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray()
    {
        const char* typeName = typeid(T).name();

        assert(ComponentTypes.find(typeName) != ComponentTypes.end() && "Componenet has not been registered");

        return std::static_pointer_cast<ComponentArray<T>>(ComponentArrays[typeName]);
    }

public:
    template<typename T>
    void RegisterComponent()
    {
        const char* typeName = typeid(T).name();
        assert(ComponentTypes.find(typeName) == ComponentTypes.end() && "Component already registered");

        ComponentTypes.insert({ typeName, NextComponentType });
        ComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

        ++NextComponentType;
    }

    template<typename T>
    ECSConstants::ComponentType GetComponentType()
    {
        const char* typeName = typeid(T).name();

        assert(ComponentTypes.find(typeName) != ComponentTypes.end() && "Componenet does not exist and therefore cannot be used.");

        return ComponentTypes[typeName];
    }

    template<typename T>
    void AddComponent(ECSConstants::Entity entity, T component)
    {
        GetComponentArray<T>()->InsertComponent(entity, component);
    }

    template<typename T>
    void RemoveComponent(ECSConstants::Entity entity)
    {
        GetComponentArray<T>()->RemoveComponent(entity);
    }

    template<typename T>
    T& GetComponent(ECSConstants::Entity entity)
    {
        return GetComponentArray<T>()->GetComponent(entity);
    }

    void EntityDestroyed(ECSConstants::Entity entity);
};