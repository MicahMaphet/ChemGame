#pragma once

#include "sprite.h"
#include "item_data.h"
#include "raylib.h"
#include "vector"
#include <map>

using std::vector;
using std::map;

struct Chemical {
    string name;
    Texture2D image;
};

struct Equation {
    vector<Chemical> reactants;
    vector<Chemical> products;
    int fill = 0;
};

class Factory : public Sprite {
public:
    Factory();
    void Render();
    map<string, bool> reactantStatuses;
    vector<Equation> equations;
    vector<Chemical> validReactants;
    vector<Chemical> placedReactants;

    float timeFilled;
    bool validReactant;
    Equation fullfilledEquation;
    bool filled = false;
    bool Place(string reactant);
    void AddEquation(vector<ItemData> reactants, vector<ItemData> products);
};