#pragma once

#include <unordered_map>
#include <memory>
#include <typeinfo>

#include "System.h"

class SystemManager
{//implement self registration for system latter.
private:
    std::unordered_map<const char*, ECSConstants::Signature> Signatures{};
    std::unordered_map<const char*, std::shared_ptr<System>> Systems{};

public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        assert(Systems.find(typeName) == Systems.end() && "System already registered");

        auto system = std::make_shared<T>();
        Systems.insert({ typeName, system });
        return system;
    }

    template<typename T>
    void SetSignature(ECSConstants::Signature signature)
    {
        const char* typeName = typeid(T).name();

        assert(Systems.find(typeName) != Systems.end() && "System has yet to be registered");

        Signatures.insert({ typeName, signature });
    }

    void EntityDestroyed(ECSConstants::Entity entity);

    void EntitySignatureChanged(ECSConstants::Entity entity, ECSConstants::Signature entitySignature);
};