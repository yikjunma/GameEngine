#include "PhysicsSystem.h"
#include "EntityComponentSystemInterface.h"
#include "RigidBodyComponent.h"
#include "GravityComponent.h"
#include "TransformComponent.h"

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