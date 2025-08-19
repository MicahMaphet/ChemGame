#pragma once

#include "sprite.h"
#include "raylib.h"
#include "vector"
#include <map>

using std::vector;
using std::map;

class BlackPowderFactory : public Sprite {
public:
    BlackPowderFactory();
    void Render();
    map<string, bool> ingredientStatuses{
        {"S", false}, {"C", false}, {"KNO3", false}
    };
    vector<string> ingredients;
    bool pickedUp;
    int filled;
    void Place(string ingredient);
    Texture2D blackPowderImage;
    Texture2D blackPowderHighlightedImage;
};