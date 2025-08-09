cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(ECSDemo VERSION 0.1 
				DESCRIPTION "Demo for ECS design patterns" 
				LANGUAGES CXX)

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

add_subdirectory(Core)
add_executable(ECSDemo App/src/App.cpp)
target_link_libraries(ECSDemo PUBLIC Core)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE raygui)

target_include_directories(ECSDemo PUBLIC
            "${PROJECT_BINARY_DIR}"
			"${PROJECT_SOURCE_DIR}/Core/src"
            )
