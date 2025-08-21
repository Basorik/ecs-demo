#include "core/Logger.h"
#include "core/Utils.h"
#include "core/Coordinator.h"
#include "raylib.h"
#include "game/GameManager.h"
#include "ui/UIManager.h"


Core::Coordinator gCoordinator;
int main() {

	const int screenWidth = 1200;
	const int screenHeight = 800;
	const char* title = "Raylib ECS Example";
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, title);
	SetTargetFPS(60); // Set the target FPS


	float dt = 0.0f;
	GameManager gameManager;
	UIManager uiManager(gameManager);
	uiManager.init(); // Initialize the UI manager and systems
	gameManager.initGameplay(screenWidth, screenHeight, 500); // Initialize the game manager and systems
	bool shouldExit = false;


	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------
		dt = GetFrameTime(); // Get the time elapsed since the last frame

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);
		
		
		uiManager.update(); // Update the UI manager and systems
		if (uiManager.shouldExit()) {
			gameManager.setGameScreen(ENDING); // Transition to the ending screen if exit is requested
		}

		GameScreen currentScreen = gameManager.getGameScreen();
		switch (currentScreen)
		{
		case LOGO:
			DrawText("Logo Screen", GetScreenWidth() / 2 - MeasureText("Logo Screen", 20) / 2, GetScreenHeight() / 4, 20, DARKGRAY);

			DrawText("Press Enter to Continue", GetScreenWidth() / 2 - MeasureText("Press Enter to Continue", 20) / 2, GetScreenHeight() / 2, 20, DARKGRAY);
			if (IsKeyPressed(KEY_ENTER)) {
				gameManager.setGameScreen(TITLE); // Transition to the title screen
			}
			break;
		case TITLE:
			break;
		case GAMEPLAY:
			gameManager.updateWindowSize(GetScreenWidth(), GetScreenHeight()); // Update the game manager with the new window size
			gameManager.update(dt); // Update the game manager and systems
			break;
		case PAUSE:
			break;
		case ENDING:
			DrawText("Ending Screen", GetScreenWidth() / 2 - MeasureText("Ending Screen", 20) / 2, GetScreenHeight() / 4, 20, DARKGRAY);
			DrawText("Press Enter to Exit", GetScreenWidth() / 2 - MeasureText("Press Enter to Exit", 20) / 2, GetScreenHeight() / 2, 20, DARKGRAY);
			if (IsKeyPressed(KEY_ENTER)) {
				shouldExit = true; // Set the exit flag to true
			}

			break;
		default:
			break;
		}
		
		



		EndDrawing();
		if (shouldExit) {
			break; // Exit the game loop if the exit flag is set
		}
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context 
	//--------------------------------------------------------------------------------------

    // Log the successful exit of the game
    Core::Logger::log(Core::Logger::Level::Info, "Game exited successfully.");
    return 0;
}
