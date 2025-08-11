#include "work_bench.h"
#include "raylib.h"
#include <iostream>

WorkBench::WorkBench(int x, int y, int width, int height) : Moveable(x, y, width, height) {
    image = LoadTexture("images/ChemBoard.png");
    highlightedImage = LoadTexture("images/HighlightedChemBoard.png");
}

void WorkBench::Render() {
    Moveable::Render();
    Rectangle rect = {0.0f, 0.0f, 100, 100};
    Vector2 pos = {100, 300};
    if (MouseHover())
        RenderImage(highlightedImage);
    else
        RenderImage(image);
}
