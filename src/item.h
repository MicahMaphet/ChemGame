#pragma once

#include "raylib.h"
#include "sprite.h"
#include "item_data.h"

class Item : public Sprite {
public:
    Item(int x, int y, int width, int height, Texture2D image, Texture2D highlihgtImg, string name);
    Item(int x, int y, ItemData data);
    Item(Vector2 pose, ItemData data);
    void Render();
    Texture2D highlightedImage;
};