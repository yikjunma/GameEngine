#pragma once

#include "src/CoreFramework/System.h"

class PhysicsSystem : public System
{
public:
    void Init();

    void Update(float dt);
};