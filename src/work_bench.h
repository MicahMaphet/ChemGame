#pragma once

#include "moveable.h"
#include "raylib.h"

class WorkBench : public Moveable {
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