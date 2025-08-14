#include "sprite.h"
#include <vector>
using std::vector;

class Inventory : public Sprite {
private:
    vector<Sprite> items;
    Sprite noitem;
    Texture2D noimage;
    int selectedItemIndex;
public:
    Inventory(int width, int height);
    void Render();
    Sprite GetSelectedItem();
    void AddItem(Sprite sprite);
    void PopItem(string item_name);
};