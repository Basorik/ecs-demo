#include "game/GameManager.h"
#include "core/Logger.h"
#include "core/Utils.h"
#include "core/Coordinator.h"
#include "core/components/Transform.h"
#include "core/components/Sprite.h"
#include "core/components/RigidBody.h"
#include "core/components/Gravity.h"
#include "core/ECS.h"
#include <random>
#include "raylib.h"

void GameManager::initGameplay(int width, int height, int count)
{	
	this->updateWindowSize(width, height);
	// Use the logger and utils at the start of the application
	Core::Logger::log(Core::Logger::Level::Info, "Starting game...");

	gCoordinator.Init();
	gCoordinator.registerComponent<Core::TransformComponent>();
	gCoordinator.registerComponent<Core::SpriteComponent>();
	gCoordinator.registerComponent<Core::RigidBodyComponent>();
	gCoordinator.registerComponent<Core::GravityComponent>();

	Core::Signature physicsSignature;
	// Register the physics system

	mPhysicsSystem = gCoordinator.registerSystem<Core::PhysicsSystem>();

	physicsSignature.set(gCoordinator.getComponentType<Core::TransformComponent>(), true);
	physicsSignature.set(gCoordinator.getComponentType<Core::RigidBodyComponent>(), true);
	physicsSignature.set(gCoordinator.getComponentType<Core::GravityComponent>(), true);
	// Register the physics system with the coordinator
	gCoordinator.setSystemSignature<Core::PhysicsSystem>(physicsSignature);



	//register render system
	Core::Signature renderSignature;
	mRenderSystem = gCoordinator.registerSystem<Core::RenderSystem>();
	renderSignature.set(gCoordinator.getComponentType<Core::SpriteComponent>(), true);
	gCoordinator.setSystemSignature<Core::RenderSystem>(renderSignature);

	mGameState.Entities.reserve(Core::MAX_ENTITIES);

	createEntities(count); // Create entities with the specified count

	

}

void GameManager::update(float dt)
{
	mPhysicsSystem->Update(GetFrameTime()); // Update the physics system with the delta time
	mRenderSystem->update(mGameWidth, mGameHeight);
}

void GameManager::createEntities(int count)
{
	if (mGameState.Entities.size() + count > Core::MAX_ENTITIES) {
		Core::Logger::log(Core::Logger::Level::Error, "Cannot create more entities than the maximum limit.");
		return;
	}
	std::vector<Color> colors = {
	RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, PINK
	};

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(0.f, 100.f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(0.005f, 0.1f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);
	std::uniform_int_distribution<int> randColor(0, colors.size() - 1);

	Texture2D ratTexture2 = LoadTexture("resources/rat.png");
	if (ratTexture2.id == 0) {
		Core::Logger::log(Core::Logger::Level::Error, "Failed to load texture: resources/rat.png");
	}
	std::shared_ptr<Texture2D> ratTexture = std::make_shared<Texture2D>(LoadTexture("resources/rat.png"));

	for (int i = 0; i < count; i++) {
		Core::Entity entity = gCoordinator.createEntity();
		mGameState.Entities.emplace_back(entity);
		gCoordinator.addComponent<Core::TransformComponent>(entity, Core::TransformComponent{
			.position = { randPosition(generator), randPosition(generator) },
			.rotation = { randRotation(generator), randRotation(generator) },
			.scale = { randScale(generator), randScale(generator) }
			});
		gCoordinator.addComponent<Core::SpriteComponent>(entity, Core::SpriteComponent{
			.texture = ratTexture, // Load your texture here
			.tint = colors[randColor(generator)]
			});
		gCoordinator.addComponent<Core::RigidBodyComponent>(entity, Core::RigidBodyComponent{
			.velocity = { 0.0f, 0.0f },
			.acceleration = { 0.0f, 0.0f }
			});
		gCoordinator.addComponent<Core::GravityComponent>(entity, Core::GravityComponent{
			.force = { 0.0f, randGravity(generator) }
			});
		Core::Logger::log(Core::Logger::Level::Info, "Entity Created");
	}
}

void GameManager::deleteEntities()
{
	for (auto& entity : mGameState.Entities) {
		gCoordinator.destroyEntity(entity);
	}
	mGameState.Entities.clear();
	Core::Logger::log(Core::Logger::Level::Info, "Entities Deleted");

}
