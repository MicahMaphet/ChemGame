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
};

class Factory : public Sprite {
private:
    void ReorgMyEquation();
    map<string, bool> reactantStatuses;
    vector<Equation> equations;
    vector<Chemical> validReactants;
    Equation fullfilledEquation;
    vector<Sprite> placedReactants;
    vector<Sprite> pendingProducts;
public:
    Factory();
    void Render();
    bool filled = false;
    bool Place(string reactant);
    void AddEquation(vector<ItemData> reactants, vector<ItemData> products);
    void ValidateMyEquation();
    void PopReactant(string reactant);
    Sprite DiscardListen();
    vector<Sprite> React();
};