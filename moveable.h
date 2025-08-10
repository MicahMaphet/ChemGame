#pragma once

#include "raylib.h"

class Moveable {
public:
    Moveable();
    int x, y;
    Texture2D texture;
    void Render();
};
