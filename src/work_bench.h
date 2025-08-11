#pragma once

#include "moveable.h"
#include "raylib.h"

class WorkBench : public Moveable {
public:
    WorkBench(int x, int y, int width, int height);
    void Render();
    Texture2D image;
    Texture2D highlightedImage;
};