#pragma once

#include "raylib.h"
#include <cmath>

struct Dimentions { int width, height; };
struct State2D { 
    Vector2 pose;
    Dimentions dims;
    float rotation;
    void Set(int x, int y, int width, int height, float rot = 0);
};

struct PositionRotation {
    float x, y;
    float rotation = 0;
};

class Util {
public:
    static void RenderImage(Texture2D image, int x, int y, int width, int height, int rotation=0, int scale=1, unsigned char alpha=255);
};

double sigmoid(double k);