#pragma once

#include "sprite.h"
#include "raylib.h"

class BlackPowderFactory : public Sprite {
public:
    BlackPowderFactory();
    void Render();
    bool hasKNO3, hasC, hasS;
    int filled;
    Texture2D blackPowderImage;
    Texture2D blackPowderHighlightedImage;
};