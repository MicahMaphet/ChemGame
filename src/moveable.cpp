#include "moveable.h"

bool Moveable::IsTouching(Moveable moveable) {
    return moveable.x + moveable.width >= x && moveable.x <= x + width &&
           moveable.y + moveable.height >= y && moveable.y <= y + height;
}

void Moveable::Render() {
    DrawRectangle(x, y, width, height, RED);
}

Moveable::Moveable(int _x, int _y, int _width, int _height) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;
}
Moveable::Moveable() {
    x, y = 0;
    ShowBox = false;
}