cmake_minimum_required(VERSION 3.16)
project(xo-game-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Version 1: console game (no dependencies)
add_executable(xo-console console/xo-game.cpp)

# Version 2: GUI game with SFML 3
find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_executable(xo-gui gui/main.cpp gui/game.cpp)
target_link_libraries(xo-gui PRIVATE SFML::Graphics)
