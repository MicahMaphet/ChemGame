#pragma once

#include "sprite.h"
#include "raylib.h"

class BlackPowderFactory : public Sprite {
private:
    Texture2D blackPowderImage;
    Texture2D blackPowderHighlightedImage;
public:
    BlackPowderFactory();
    void Render();
    bool hasKNO3, hasC, hasS;
};