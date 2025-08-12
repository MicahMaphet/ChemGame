#pragma once

#include "sprite.h"
#include "raylib.h"

class WorkBench : public Sprite {
private:
    Texture2D image;
    Texture2D highlightedImage;
    enum State {
        Displaying,
        NotDisplaying
    };
    State state;
    State2D realState2D;
    State2D displayState2D;
public:
    WorkBench(int x, int y, int width, int height);
    void Render();
    void Display();
    void EndDisplay();
};