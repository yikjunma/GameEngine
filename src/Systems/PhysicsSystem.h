#pragma once

#include "src/System.h"

class PhysicsSystem : public System
{
public:
    void Init();

    void Update(float dt);
};