#pragma once

#include "sprite.h"
#include "raylib.h"
#include "vector"
#include <map>

using std::vector;
using std::map;

class Factory : public Sprite {
public:
    Factory(vector<string> ingredientsList);
    void Render();
    map<string, bool> ingredientStatuses;
    vector<string> ingredients;
    bool IsFilled();
    int filled;
    void Place(string ingredient);
};