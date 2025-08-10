#pragma once

#include "raylib.h"
#include <string>

class Moveable {
public:
    Moveable();
    int x, y;
    Texture2D texture;
    void Render();
};
