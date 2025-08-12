#include "level.h"
#include <vector>
using std::vector;

Level::Level() : level(0) {
    positions = {
        State2D{1900, 500, 100, 200},
        State2D{300, 900, 100, 100},
        State2D{1900, 800, 100, 200},
        State2D{300, 900, 100, 200},
    };
    NextLevel();
}

void Level::NextLevel() {
    SetByState2D(positions[level]);
    level++;
}