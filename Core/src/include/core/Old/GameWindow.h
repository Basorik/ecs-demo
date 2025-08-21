#pragma once

#include "Coordinator.h"
#include "systems/RenderSystem.h"
#include <memory>
#include <string>
#include <unordered_map>
#include "raylib.h"

namespace Core {

    class GameWindow {
    public:
        GameWindow(int width, int height, const std::string& title);
        ~GameWindow();
        void run();

    private:
        void update();
        void render();

        void initECS();
        void loadAssets();

        // ECS
        Coordinator mCoordinator;
        std::shared_ptr<RenderSystem> mRenderSystem;

        // A simple texture manager for Raylib textures
        std::unordered_map<std::string, std::shared_ptr<Texture2D>> mTextureManager;
    };

} // namespace core
