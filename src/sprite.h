#pragma once

#include "raylib.h"
#include "util.h"
#include <string>
using std::string;

class Sprite {
public:
    void SetByState2D(State2D state2D);
    void SetByPose(Vector2 pose);
    void SetByDims(Dimentions pose);
    Sprite(int x, int y, int width, int height, string name);
    Sprite(int x, int y, int width, int height);
    Sprite(int x, int y, int width, int height, Texture2D img, string name);
    Sprite(int width, int height);
    Sprite(int width, int height, Texture2D img, string name);
    Sprite(int width, int height, string name);
    Sprite();
    int x, y, width, height;
    double heading, rotation, speed, speedX, speedY, maxSpeed, speedDeadband, acceleration;
    bool ShowBox;
    string name;
    Texture2D image;
    bool IsTouching(Sprite sprite);
    bool IsMouseHover();
    bool IsClicked();
    void MouseDragListen();
    double GetMouseAngle();
    double GetMouseDistance();
    void Render();
    void RenderImage(Texture2D image, float scale = 1);
    void RenderImage(float scale = 1);
    bool GetOffScreen();
};