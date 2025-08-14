#include "item.h"
#include <string.h>
#include <iostream>

Item::Item(int x, int y, int width, int height, string img, string name)
: Sprite(x, y, width, height, LoadTexture(img.c_str()), name) {
    int imageFilePeriod = img.find_last_of(".");

    highlightedImage = LoadTexture(
        (img.substr(0, imageFilePeriod) + "Highlighted" +
         img.substr(imageFilePeriod, img.length())).c_str());
}

void Item::Render() {
    Sprite::Render();
    if (IsMouseHover())
        RenderImage(highlightedImage);
    else
        RenderImage();
}