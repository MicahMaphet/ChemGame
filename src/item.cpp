#include "item.h"
#include <string.h>
#include <iostream>
#include "raylib.h"

Item::Item(int x, int y, int width, int height, Texture2D image, Texture2D highlightImg, string name)
: Sprite(x, y, width, height, image, name) {
    highlightedImage = highlightImg;
    std::cout << "\nconstructed item name " << name;
}

Item::Item(int x, int y, ItemData data) : Item(x, y, data.width, data.height, data.image, data.highlightedImage, data.name) {}
Item::Item(Vector2 pose, ItemData data) : Item(pose.x, pose.y, data) {}

void Item::Render() {
    Sprite::Render();
    if (IsMouseHover())
        RenderImage(highlightedImage);
    else
        RenderImage();
}