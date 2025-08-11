#include "level.h"
#include <vector>
using std::vector;

Level::Level() : level(0) {
    positions = {
        {1900, 500, 100, 200},
        {300, 900, 100, 100},
        {1900, 800, 100, 200},
        {300, 900, 100, 200},
    };
    NextLevel();
}

void Level::NextLevel() {
    x = positions[level][0];
    y = positions[level][1];
    width = positions[level][2];
    height = positions[level][3];
    level++;
}