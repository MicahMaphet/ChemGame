#pragma once

#include "sprite.h"
#include "item_data.h"
#include "raylib.h"
#include "vector"
#include <map>

using std::vector;
using std::map;

class Factory : public Sprite {
public:
    Factory(vector<ItemData> reactantsList, string product);
    void Render();
    map<string, bool> reactantStatuses;
    vector<ItemData> reactants;
    bool IsFilled();
    int filled;
    float timeFilled;
    float timeToFade = 5;
    string product;
    void Place(string reactant);
    bool SniffItem(Sprite &item);
};