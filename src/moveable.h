#pragma once

#include "raylib.h"

class Moveable {
public:
    Moveable(int x, int y, int width, int height);
    Moveable();
    int x, y, width, height;
    double heading, speed, speedX, speedY, maxSpeed, speedDeadband, acceleration;
    bool ShowBox;
    bool IsTouching(Moveable moveable);
    bool MouseHover();
    bool Clicked();
    void Render();
    void RenderImage(Texture2D image);
};