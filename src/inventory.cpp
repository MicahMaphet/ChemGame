#include "inventory.h"

Inventory::Inventory(int width, int height) : Sprite(0, 0, width, height) {
    items = {
        Sprite{0, 0, 200, 200},
        Sprite{0, 0, 100, 100},
        Sprite{0, 0, 100, 100}
    };
    itemImages = {
        LoadTexture("images/KNO3.png"),
        LoadTexture("images/C.png"),
        LoadTexture("images/S.png")
    };
}

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
            Rectangle rect{originX + padding + row * (boxWidth + padding),
                           originY + padding + col * (boxWidth + padding), 
                           (float)boxWidth, (float)boxWidth};
            bool hover = rect.x < GetMousePosition().x && rect.x + rect.width > GetMousePosition().x &&
                         rect.y < GetMousePosition().y && rect.y + rect.height > GetMousePosition().y;
            DrawRectangleLinesEx(rect, 10, hover ? WHITE : GRAY);
            Sprite item = items[row + col * numBoxs];
            Texture2D image = itemImages[row + col * numBoxs];
            item.x = originX + padding + row * (boxWidth + padding) + boxWidth/2;
            item.y = originY + padding + col * (boxWidth + padding) + boxWidth/2;
            item.RenderImage(image);
        }
    }
}