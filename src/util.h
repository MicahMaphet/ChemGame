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

class Util {
public:
    static void RenderImage(Texture2D image, int x, int y, int width, int height, int rotation, int scale);
};

double sigmoid(double k);