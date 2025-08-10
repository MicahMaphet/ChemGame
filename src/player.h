#pragma once

#include "raylib.h"
#include "moveable.h"

class Player: public Moveable {
private:
    Texture2D texture;
public:
    Player(int x, int y, int width, int height);
    void KeyListen();
    void Render();
};