#include "inventory.h"
#include <iostream>

Inventory::Inventory(int width, int height) : Sprite(width, height) {
    noitem.name = "noitem";
    selectedItemIndex = -1;
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
                item.x = rect.x + boxWidth/2;
                item.y = rect.y + boxWidth/2;
                item.RenderImage(item.image);
                if (itemCounts.at(item.name) > 1)
                    DrawText(TextFormat("x%i", itemCounts.at(item.name)), rect.x+boxWidth-50, rect.y+15, 30, hover ? WHITE : GRAY);
                if (hover) {
                    Vector2 labelOrigin = {-rect.x-10, -rect.y-boxWidth*0.8f+10};
                    DrawRectanglePro(Rectangle{0, 0, (float)boxWidth-20, (float)boxWidth*0.2f}, 
                                 labelOrigin, 0, {50, 50, 50, 200});
                    DrawText(item.name.c_str(), -labelOrigin.x+10, -labelOrigin.y+10, 16, WHITE);
                    if (IsMouseButtonReleased(0)) {
                        selectedItemIndex = itemIndex;
                    }
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
    if (itemCounts.count(sprite.name) == 0) {
        items.push_back(sprite);
        itemCounts.insert({sprite.name, 1});
    } else {
        itemCounts.at(sprite.name)++;
    }
}

void Inventory::AddItem(ItemData itemd) {
    AddItem({itemd.width, itemd.height, itemd.image, itemd.name});
}

void Inventory::AddItem(Item item) {
    AddItem({item.width, item.height, item.image, item.name});
}

void Inventory::PopItem(string item_name) {
    if (itemCounts.count(item_name) == 0)
        return;
    if (itemCounts.at(item_name) > 1) {
        itemCounts.at(item_name)--;
        return;
    }
    itemCounts.erase(item_name);
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