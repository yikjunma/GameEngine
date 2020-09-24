#include "ComponentManager.h"

void ComponentManager::EntityDestroyed(ECSConstants::Entity entity)
{
    for (auto const& pair : ComponentArrays)
    {
        auto const& component = pair.second;

        component->EntityDestroyed(entity);
    }
}