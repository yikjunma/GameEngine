#include "PhysicsSystem.h"
#include "src/EntityComponentSystemInterface.h"
#include "src/Components/RigidBodyComponent.h"
#include "src/Components/GravityComponent.h"
#include "src/Components/TransformComponent.h"

extern EntityComponentSystemInterface gCoordinator;


void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update(float dt)
{
	for (auto const& entity : Entities)
	{
		auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);

		// Forces
		auto const& gravity = gCoordinator.GetComponent<Gravity>(entity);

		transform.Position += rigidBody.Velocity * dt;

		rigidBody.Velocity += gravity.Force * dt;
	}
}