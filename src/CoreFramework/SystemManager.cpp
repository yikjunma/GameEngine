#include "SystemManager.h"

void SystemManager::EntityDestroyed(ECSConstants::Entity entity)
{
    for (auto const& pair : Systems)
    {
        auto const& system = pair.second;
        system->Entities.erase(entity);
    }
}

void SystemManager::EntitySignatureChanged(ECSConstants::Entity entity, ECSConstants::Signature entitySignature)
{
    for (auto const& pair : Systems)
    {
        auto const& type = pair.first;
        auto const& system = pair.second;
        auto const& systemSignature = Signatures[type];

        if ((entitySignature & systemSignature) == systemSignature)
        {
            system->Entities.insert(entity);
        }
        else
        {
            system->Entities.erase(entity);
        }
    }
}