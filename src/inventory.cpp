#include "inventory.h"

Inventory::Inventory(int width, int height) : Sprite(0, 0, width, height) {}

void Inventory::Render() {
    Sprite::Render();
    DrawRectangleLinesEx(Rectangle{
        (float)GetScreenWidth()/2 - width/2, (float)GetScreenHeight()/2 - height/2,
        (float)width, (float)height},
        10, WHITE);
    int padding = 20;
    int numBoxs = 4;
    int boxWidth = width / numBoxs - padding - padding/numBoxs;
    float originX = GetScreenWidth()/2 - width/2;
    float originY = GetScreenHeight()/2 - height/2;
    for (int row = 0; row < numBoxs; row++) {
        for (int col = 0; col < numBoxs; col++) {
            DrawRectangleLinesEx(
                Rectangle{originX + padding + row * (boxWidth + padding),
                          originY + padding + col * (boxWidth + padding), 
                          (float)boxWidth, (float)boxWidth},
                10, WHITE
            );
        }
    }
}