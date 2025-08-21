#include "ui/UIManager.h"
#include "core/components/Sprite.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

void UIManager::init()
{

	//register render system
	//Core::Signature renderSignature;
	//mRenderSystem = gCoordinator.registerSystem<Core::RenderSystem>();
	//renderSignature.set(gCoordinator.getComponentType<Core::SpriteComponent>(), true);
	//gCoordinator.setSystemSignature<Core::RenderSystem>(renderSignature);

}

void UIManager::update()
{
	GameScreen currentScreen = mGameManager.getGameScreen();
    if (currentScreen == TITLE)
    {
        // Draw title
        DrawText("Entity Component System Demo", GetScreenWidth() / 2 - MeasureText("Entity Component System Demo", 40) / 2, GetScreenHeight() / 4, 40, DARKGRAY);

        // Draw buttons
        if (GuiButton(Rectangle{ (float)GetScreenWidth() / 2 - 100, (float)GetScreenHeight() / 2 - 50, 200, 50 }, "Start Game"))
        {
            mGameManager.setGameScreen(GAMEPLAY);
        }
        if (GuiButton(Rectangle{ (float)GetScreenWidth() / 2 - 100, (float)GetScreenHeight() / 2 + 20, 200, 50 }, "Options"))
        {
            mShowOptions = !mShowOptions;
        }
        if (GuiButton(Rectangle{ (float)GetScreenWidth() / 2 - 100, (float)GetScreenHeight() / 2 + 90, 200, 50 }, "Exit"))
        {
            mExitWindow = true;
        }

        // Options window
        if (mShowOptions)
        {
            int result = GuiWindowBox(Rectangle{ (float)GetScreenWidth() / 2 - 150, (float)GetScreenHeight() / 2 - 100, 300, 200 }, "Options");
            if (result == -1 || result == 1) // Closed or OK pressed
            {
                mShowOptions = false;
            }

        }
    }
    else if (currentScreen == GAMEPLAY)
    {
        // Gameplay UI can be drawn here
        // For example, draw the score, health, etc.
        DrawText("Gameplay Screen", GetScreenWidth() / 2 - MeasureText("Gameplay Screen", 20) / 2, GetScreenHeight() / 4, 20, DARKGRAY);

        // Pause button
        if (GuiButton(Rectangle{ (float)GetScreenWidth() - 120, 20, 100, 30 }, "Add"))
        {
            mGameManager.createEntities(500);
        }

        if (GuiButton(Rectangle{ (float)GetScreenWidth() - 120, 60, 100, 30 }, "Delete"))
        {
            mGameManager.deleteEntities();
        }

        if (GuiButton(Rectangle{ (float)GetScreenWidth() - 120, 100, 100, 30 }, "Back to Menu"))
        {
            mGameManager.deleteEntities();
            mGameManager.setGameScreen(TITLE);
		}
    }
}