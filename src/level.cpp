#include "level.h"
#include <vector>
#include "raylib.h"
using std::vector;

Level::Level() : level(0) {
    defaultImage = LoadTexture("images/Door.png");
    positions = {
        State2D{1900, 500, 40, 120, 0},
        State2D{300, 900, 40, 120, 90},
        State2D{1900, 800, 40, 120, 180},
        State2D{300, 900, 40, 120, 360},
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