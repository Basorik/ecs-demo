#pragma once
#include "../ECS.h"
#include "../Coordinator.h"

namespace Core
{
	class PhysicsSystem : public System
	{
	public:
		void Init();

		void Update(float dt);
	};

}