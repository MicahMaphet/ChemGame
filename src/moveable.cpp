#include "moveable.h"

bool Moveable::IsTouching(Moveable moveable) {
    return moveable.x + moveable.width >= x && moveable.x <= x + width &&
           moveable.y + moveable.height >= y && moveable.y <= y + height;
}

void Moveable::Render() {
    if (ShowBox)
        DrawRectangle(x, y, width, height, RED);
}

Moveable::Moveable(int x, int y, int width, int height) : x(x), y(y), width(width), height(height),
    heading(0), speed(0), speedX(0), speedY(0), maxSpeed(0), speedDeadband(2), acceleration(0) {}

Moveable::Moveable() : Moveable(0, 0, 0, 0) {
    ShowBox = false;
}