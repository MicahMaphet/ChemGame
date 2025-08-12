#include "work_bench.h"
#include "raylib.h"
#include <iostream>

WorkBench::WorkBench(int x, int y, int width, int height) : Moveable(x, y, width, height) {
    realState2D.Set(x, y, width, height);
    displayState2D.Set(GetScreenWidth()/2, GetScreenHeight()/2, GetScreenWidth() - 100, GetScreenHeight() - 100);
    state = NotDisplaying;
    image = LoadTexture("images/ChemBoard.png");
    highlightedImage = LoadTexture("images/HighlightedChemBoard.png");
}

void WorkBench::Render() {
    Moveable::Render();
    if (MouseHover() && state == NotDisplaying)
        RenderImage(highlightedImage);
    else RenderImage(image);
}

void WorkBench::Display() {
    state = Displaying;
    SetByState2D(displayState2D);
}

void WorkBench::EndDisplay() {
    state = NotDisplaying;
    SetByState2D(realState2D);
}