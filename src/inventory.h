#include "sprite.h"
#include <vector>
using std::vector;

class Inventory : public Sprite {
private:
    vector<Sprite> items;
    vector<Texture2D> itemImages;
    int selectedItemIndex;
public:
    Inventory(int width, int height);
    void Render();
    Sprite GetSelectedItem();
    Texture2D GetSelectedItemImage();
    void AddItem(Sprite sprite, Texture2D image);
};