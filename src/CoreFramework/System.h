#pragma once
#include <set>

#include "ECSConstants.h"

class System
{
public:
    std::set<ECSConstants::Entity> Entities;
};