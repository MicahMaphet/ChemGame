#pragma once

#include "raylib.h"
#include "sprite.h"

class Player: public Sprite {
private:
    Texture2D texture;
    void Hold();
public:
    Player();
    void KeyListen();
    void Render();
    void Deaccelerate();
    void SelectItem(Sprite item);
    Sprite item{100, 100, "noitem"};
};