#include "sprite.h"

class Item : public Sprite {
public:
    Item(int x, int y, int width, int height, Texture2D image, Texture2D highlightedImage, string name);
    void Render();
    Texture2D highlightedImage;
};