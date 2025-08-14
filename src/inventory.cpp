#include "inventory.h"
#include <iostream>

Inventory::Inventory(int width, int height) : Sprite(width, height) {
    items = {
        Sprite{200, 200, "KNO3"},
        Sprite{100, 100, "C"},
        Sprite{100, 100, "S"}
    };

    itemImages = {
        LoadTexture("images/KNO3.png"),
        LoadTexture("images/C.png"),
        LoadTexture("images/S.png")
    };
    selectedItemIndex = 0;
}

void Inventory::Render() {
    Sprite::Render();
    Rectangle shell = {
        (float)GetScreenWidth()/2 - width/2, (float)GetScreenHeight()/2 - height/2,
        (float)width, (float)height};
    DrawRectangleLinesEx(shell, 10, WHITE);
    int padding = 20;
    int numBoxs = 4;
    int boxWidth = width / numBoxs - padding - padding/numBoxs;
    for (int row = 0; row < numBoxs; row++) {
        for (int col = 0; col < numBoxs; col++) {
            Rectangle rect{shell.x + padding + row * (boxWidth + padding),
                           shell.y + padding + col * (boxWidth + padding), 
                           (float)boxWidth, (float)boxWidth};
            bool hover = rect.x < GetMouseX() && rect.x + rect.width > GetMouseX() &&
                         rect.y < GetMouseY() && rect.y + rect.height > GetMouseY();
            DrawRectangleLinesEx(rect, 10, hover ? WHITE : GRAY);
            int itemIndex = row + col * numBoxs;
            if (itemIndex < items.size()) {
                Sprite item = items[itemIndex];
                Texture2D image = itemImages[itemIndex];
                item.x = shell.x + padding + row * (boxWidth + padding) + boxWidth/2;
                item.y = shell.y + padding + col * (boxWidth + padding) + boxWidth/2;
                item.RenderImage(image);
                if (hover && IsMouseButtonReleased(0)) {
                    selectedItemIndex = itemIndex;
                }
            }
        }
    }
}

Sprite Inventory::GetSelectedItem() {
    return items[selectedItemIndex];
}

Texture2D Inventory::GetSelectedItemImage() {
    return itemImages[selectedItemIndex];
}