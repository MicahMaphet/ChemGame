#include "moveable.h"
#include "raylib.h"

Moveable::Moveable() {
    texture = LoadTexture("./image.png");
    x = 0;
    y = 0;
}

void Moveable::Render() {
    DrawTexture(texture, x, y, WHITE);
}