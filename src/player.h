#pragma once

#include "raylib.h"
#include "sprite.h"

class Player: public Sprite {
private:
    Texture2D texture;
    void Hold();
public:
    Player(int x, int y, int width, int height);
    void KeyListen();
    void Render();
    void Deaccelerate();
    Sprite item;
    Texture2D itemImage;
};