#include "character.h"
#include "raylib.h"

Character::Character() {
    texture = LoadTexture("./image.png");
}

void Character::Render() {
    Moveable::Render();
    DrawTexture(texture, x, y, WHITE);
}