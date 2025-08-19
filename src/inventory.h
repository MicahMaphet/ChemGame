#include "sprite.h"
#include "item.h"
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
    void AddItem(Item item);
    void AddItem(ItemData itemd);
    void PopItem(string item_name);
};