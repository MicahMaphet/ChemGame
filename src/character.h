#pragma once

#include "raylib.h"
#include "./moveable.h"

class Character: public Moveable {
public:
    Character();
    void Render();
    Texture2D texture;
};
