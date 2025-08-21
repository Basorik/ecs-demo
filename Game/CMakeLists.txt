# Project name for the game
project(Game)

# Add the game executable
add_executable(Game
    src/main.cpp
  "src/ui/UIManager.cpp" "src/game/GameManager.cpp" "src/include/game/GameManager.h" "src/include/ui/UIManager.h" "src/game/InputManager.cpp" "src/include/game/InputManager.h" )

# Link the core library to the game
target_link_libraries(Game
    Core
    raylib
    raygui
)

target_include_directories(Core PUBLIC
            "${PROJECT_BINARY_DIR}"
			"${PROJECT_SOURCE_DIR}/src"
            "${PROJECT_SOURCE_DIR}/src/include"
            )

add_custom_command(
    TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Game/resources
        $<TARGET_FILE_DIR:Game>/resources
)