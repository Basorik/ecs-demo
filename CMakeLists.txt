cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(ECSDemo VERSION 0.1 
				DESCRIPTION "Demo for ECS design patterns" 
				LANGUAGES CXX)

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)



add_subdirectory(Core)
add_subdirectory(Game)
add_subdirectory(Tests)

if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, e.g. Debug, Release, RelWithDebInfo, MinSizeRel." FORCE)
endif()


