#include "sprite.h"
#include <vector>
using std::vector;

class Inventory : public Sprite {
private:
    vector<Sprite> items;
    vector<Texture2D> itemImages;
public:
    Inventory(int width, int height);
    void Render();
};