#include "inventory.h"
#include <iostream>

Inventory::Inventory(int width, int height) : Sprite(width, height) {
    noitem.name = "noitem";
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
                Sprite item = items.at(itemIndex);
                item.x = shell.x + padding + row * (boxWidth + padding) + boxWidth/2;
                item.y = shell.y + padding + col * (boxWidth + padding) + boxWidth/2;
                item.RenderImage(item.image);
                if (hover && IsMouseButtonReleased(0)) {
                    selectedItemIndex = itemIndex;
                }
            } else if (hover && IsMouseButtonReleased(0)) {
                selectedItemIndex = -1;
            }
        }
    }
}

Sprite Inventory::GetSelectedItem() {
    if (selectedItemIndex < 0)
        return noitem;
    return items.at(selectedItemIndex);
}

void Inventory::AddItem(Sprite sprite) {
    items.push_back(sprite);
}

void Inventory::AddItem(ItemData itemd) {
    items.push_back({itemd.width, itemd.height, itemd.image, itemd.name});
}

void Inventory::AddItem(Item item) {
    items.push_back({item.width, item.height, item.image, item.name});
}

void Inventory::PopItem(string item_name) {
    for (int i = 0; i < items.size(); i++) {
        if (items.at(i).name.compare(item_name) == 0) {
            // unselect item if removing the selected item
            if (i == selectedItemIndex)
                selectedItemIndex = -1;
            items.erase(items.begin() + i);
            return;
        }
    }
}