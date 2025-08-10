#include "level.h"
#include <vector>
using std::vector;

Level::Level() : level(0) {
    positions = {
        {0, 0, 50, 50},
        {100, 300, 100, 50},
        {200, 500, 20, 20}
    };
    Moveable(positions[level][0], positions[level][1], positions[level][2], positions[level][3]);
}

void Level::NextLevel() {
    level++;
    x = positions[level][0];
    y = positions[level][1];
    width = positions[level][2];
    height = positions[level][3];
}