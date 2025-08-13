#pragma once

#include "raylib.h"

struct Position { int x, y; };
struct Dimentions { int width, height; };
struct State2D { 
    Position pose; 
    Dimentions dims;
    float rotation;
    void Set(int x, int y, int width, int height, float rot = 0);
};

class Sprite {
public:
    void SetByState2D(State2D state2D);
    void SetByPose(Position pose);
    void SetByDims(Dimentions pose);
    void SetByVector2(Vector2 vector2);
    Sprite(int x, int y, int width, int height);
    Sprite(int width, int height);
    Sprite();
    int x, y, width, height;
    double heading, rotation, speed, speedX, speedY, maxSpeed, speedDeadband, acceleration;
    bool ShowBox;
    bool IsTouching(Sprite sprite);
    bool MouseHover();
    bool Clicked();
    void MouseDragListen();
    void Render();
    void RenderImage(Texture2D image, float scale = 1);
};