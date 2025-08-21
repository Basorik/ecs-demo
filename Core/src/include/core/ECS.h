#pragma once

#include <cstdint>
#include <set>
#include <bitset>



namespace Core {

	// Entity
	using Entity = std::uint32_t;
	const Entity MAX_ENTITIES = 5000;
	

	// Components
	using ComponentType = std::uint8_t;
	const ComponentType MAX_COMPONENTS = 32;

	// Signature is a bitset that represents the components an entity has
	using Signature = std::bitset<MAX_COMPONENTS>;

	// System is just a collection of entities
	class System {
	public:
		std::set<Entity> mEntities;
	};
}