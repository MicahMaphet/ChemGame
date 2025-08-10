#pragma once

#include "raylib.h"

class Moveable {
public:
    Moveable(int x, int y, int width, int height);
    Moveable();
    int x, y;
    int width, height;
    bool ShowBox;
    bool IsTouching(Moveable moveable);
    void Render();
};