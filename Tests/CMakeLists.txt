cmake_minimum_required(VERSION 3.24)
project(Tests)

set(CMAKE_CXX_STANDARD 20)

add_executable(RunTests
    UtilsTest.cpp
)

target_link_libraries(RunTests
    Core
    gtest_main
)

target_include_directories(RunTests PUBLIC "${CMAKE_SOURCE_DIR}/Core/src/include")

include(GoogleTest)
gtest_discover_tests(RunTests)
