#include "item.h"

Item::Item(int x, int y, int width, int height, Texture2D image, Texture2D highlightImg, string name)
: Sprite(x, y, width, height, image, name) {
    highlightedImage = highlightImg;
}

void Item::Render() {
    Sprite::Render();
    if (IsMouseHover())
        RenderImage(highlightedImage);
    else
        RenderImage();
}