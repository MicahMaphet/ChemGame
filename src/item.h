#include "sprite.h"

class Item : public Sprite {
public:
    Item(int x, int y, int width, int height, string image, string name);
    void Render();
    Texture2D highlightedImage;
};