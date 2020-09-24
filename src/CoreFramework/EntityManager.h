#pragma once
#include <queue>
#include <cassert>
#include <array>

#include "ECSConstants.h"

class EntityManager
{
private:
    std::queue<ECSConstants::Entity> AvailableEntities{};
    std::array<ECSConstants::Signature, ECSConstants::MAX_ENTITIES> EntitySignatures{};
    std::uint32_t UsedEntities{};

public:
    EntityManager();

    ECSConstants::Entity CreateEntity();

    void DestroyEntity(ECSConstants::Entity entity);

    void SetEntitySignature(ECSConstants::Entity entity, ECSConstants::Signature signature);

    ECSConstants::Signature GetentitySignature(ECSConstants::Entity entity);
};