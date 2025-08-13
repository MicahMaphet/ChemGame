#include "level.h"
#include <vector>
#include "raylib.h"
using std::vector;

Level::Level() : level(0) {
    defaultImage = LoadTexture("images/Door.png");
    positions = {
        State2D{1900, 500, 120, 40, 90},
        State2D{300, 900, 120, 40, 0},
        State2D{1900, 800, 120, 40, 360},
        State2D{300, 900, 120, 40, 180},
    };
    NextLevel();
}

void Level::Render() {
    Sprite::Render();
    RenderImage(defaultImage);
}

void Level::NextLevel() {
    SetByState2D(positions[level]);
    level++;
}