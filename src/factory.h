#pragma once

#include "sprite.h"
#include "raylib.h"
#include "vector"
#include <map>

using std::vector;
using std::map;

class Factory : public Sprite {
public:
    Factory(vector<string> reactantsList, string product);
    void Render();
    map<string, bool> reactantStatuses;
    vector<string> reactants;
    bool IsFilled();
    int filled;
    float timeFilled;
    float timeToFade = 5;
    string product;
    void Place(string reactant);
    bool SniffItem(Sprite &item);
};