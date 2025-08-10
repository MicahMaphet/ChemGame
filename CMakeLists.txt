cmake_minimum_required(VERSION 3.10.0)
project(cpp-game VERSION 0.1.0 LANGUAGES C CXX)

find_package(raylib REQUIRED)

add_executable(cpp-game src/main.cpp src/moveable.cpp src/player.cpp)
target_link_libraries(cpp-game PRIVATE raylib)
