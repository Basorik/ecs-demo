cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Core)

add_library(Core STATIC
	
	"src/Logger.cpp"
	"src/Utils.cpp"
  "src/include/core/ECS.h" "src/include/core/components/Transform.h" "src/include/core/components/Sprite.h" "src/include/core/Old/Coordinator.h" "src/include/core/systems/RenderSystem.h" "src/systems/RenderSystem.cpp" "src/include/core/Old/GameWindow.h"  "src/include/core/EntityManager.h" "src/include/core/ComponentArray.h" "src/include/core/ComponentManager.h" "src/include/core/SystemManager.h" "src/include/core/Coordinator.h" "src/include/core/components/RigidBody.h" "src/include/core/components/Gravity.h" "src/include/core/systems/PhysicsSystem.h" "src/systems/PhysicsSystem.cpp")

include(FetchContent)
function(add_git_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG        ${gitTag}
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
add_git_dependency(
    raylib
    https://github.com/raysan5/raylib.git
    5.5
)

# Special handling for raygui since its CMakeLists.txt is not at the root of the repo
set(BUILD_RAYGUI_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG        4.0
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)
FetchContent_GetProperties(raygui)
if(NOT raygui_POPULATED)
    FetchContent_Populate(raygui)
    add_subdirectory(${raygui_SOURCE_DIR}/projects/CMake raygui)
    target_compile_options(raygui INTERFACE "-w")
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
target_link_libraries(${PROJECT_NAME} PUBLIC raygui)

target_include_directories(Core PUBLIC
            "${PROJECT_BINARY_DIR}"
			"${PROJECT_SOURCE_DIR}/src"
            "${PROJECT_SOURCE_DIR}/src/include"
            )