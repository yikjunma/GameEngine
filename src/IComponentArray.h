#pragma once
#include "ECSConstants.h"

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(ECSConstants::Entity entity) = 0;
};