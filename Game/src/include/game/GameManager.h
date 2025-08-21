#pragma once
#include "InputManager.h"
#include "core/systems/PhysicsSystem.h"
#include "core/systems/RenderSystem.h"
#include <vector>
typedef enum GameScreen 
{ 
	LOGO = 0,
	TITLE,
	GAMEPLAY,
	PAUSE,
	ENDING 
} GameScreen;

struct GameState
{
	GameScreen currentScreen;
	bool isRunning;
	std::vector<Core::Entity> Entities{};
};

extern Core::Coordinator gCoordinator;
class GameManager
{
public:

	GameManager() : mGameState(GameState(GameScreen::LOGO, true)), mGameHeight(0), mGameWidth(0) {}
	void initGameplay(int width, int height, int count);
	void update(float dt);
	GameState& getGameState() { return mGameState; }
	void setGameScreen(GameScreen screen) { mGameState.currentScreen = screen; }
	GameScreen getGameScreen() const { return mGameState.currentScreen; }
	void updateWindowSize(int width, int height) {
		mGameWidth = width;
		mGameHeight = height;
	}
	void createEntities(int count);
	void deleteEntities();
private:
	GameState mGameState;
	InputManager mInputManager;
	std::shared_ptr<Core::PhysicsSystem> mPhysicsSystem;
	std::shared_ptr<Core::RenderSystem> mRenderSystem;
	int mGameWidth;
	int mGameHeight;

};