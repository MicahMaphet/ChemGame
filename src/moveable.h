#pragma once

#include "raylib.h"

class Moveable {
public:
    struct Position { int x, y; };
    struct Dimentions { int width, height; };
    struct State2D { 
        Position pose; 
        Dimentions dims;
        void Set(int x, int y, int width, int height);
    };
    void SetByState2D(State2D state2D);
    void SetByPose(Position pose);
    void SetByDims(Dimentions pose);
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