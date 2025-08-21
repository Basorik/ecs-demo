#pragma once
#include "core/Coordinator.h"
#include "game/GameManager.h"

class UIManager
{
public:
	UIManager(GameManager& gameManager) : mGameManager(gameManager), mShowOptions(false), mExitWindow(false) {}
	void init();
	void update();
	bool shouldExit() const { return mExitWindow; }
private:
	GameManager& mGameManager;
	bool mShowOptions;
	bool mExitWindow;
};