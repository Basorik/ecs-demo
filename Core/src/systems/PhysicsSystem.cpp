#include "core/systems/PhysicsSystem.h"
#include "core/Coordinator.h"
#include "core/components/RigidBody.h"
#include "core/components/Transform.h"
#include "core/components/Gravity.h"
#include "core/ECS.h"
#include "raymath.h"
#include "raylib.h"

extern Core::Coordinator gCoordinator;
namespace Core
{
	

	void PhysicsSystem::Update(float dt)
	{
		for (auto const& entity : mEntities)
		{
			auto& rigidBody = gCoordinator.getComponent<RigidBodyComponent>(entity);
			auto& transform = gCoordinator.getComponent<TransformComponent>(entity);
			auto const& gravity = gCoordinator.getComponent<GravityComponent>(entity);

			transform.position -= Vector2Scale(rigidBody.velocity,dt);

			rigidBody.velocity += Vector2Scale(gravity.force, dt);

			if (transform.position.y > 100)
			{
				transform.position.y = 0;
			}
		}
	}
}
