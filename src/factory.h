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
private:
    void ShiftPlacedReactants();
    map<string, bool> reactantStatuses;
    vector<Equation> equations;
    vector<Chemical> validReactants;
    Equation fullfilledEquation;
    vector<Sprite> placedReactants;
    vector<Sprite> pendingProducts;
public:
    Factory();
    void Render();
    float timeFilled;
    bool validReactant;
    bool filled = false;
    bool Place(string reactant);
    void AddEquation(vector<ItemData> reactants, vector<ItemData> products);
    void PopReactant(string reactant);
    Sprite DiscardListen();
    Sprite ClaimProductListen();
};