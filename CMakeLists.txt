cmake_minimum_required(VERSION 3.10.0)
project(ChemGame VERSION 0.1.0 LANGUAGES C CXX)

find_package(raylib REQUIRED)

add_executable(ChemGame src/main.cpp src/util.cpp src/sprite.cpp src/player.cpp src/level.cpp src/work_bench.cpp src/inventory.cpp src/blackpowder_factory.cpp src/item.cpp src/item_data.cpp)
target_link_libraries(ChemGame PRIVATE raylib)