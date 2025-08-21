cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(ECSDemo VERSION 0.1 
				DESCRIPTION "Demo for ECS design patterns" 
				LANGUAGES CXX)



add_subdirectory(Core)
add_subdirectory(Game)




