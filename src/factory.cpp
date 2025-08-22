#include "factory.h"
#include <iostream>
using std::cout;

Factory::Factory() : Sprite(1500, 700, 125, 100) {}

void Factory::AddEquation(vector<ItemData> reactants, vector<ItemData> products) {
    equations.push_back({{}, {}});
    for (ItemData& reactant : reactants) {
        bool alreadyValid = false;
        for (Chemical& validReactant : validReactants) {
            if (reactant.name.compare(validReactant.name) == 0) {
                alreadyValid = true;
                equations.back().reactants.push_back(validReactant);
                break;
            }
        }
        if (!alreadyValid) {
            validReactants.push_back({reactant.name, reactant.image});
            equations.back().reactants.push_back(validReactants.back());
        }
    }
    for (ItemData product : products) {
        equations.back().products.push_back({product.name, product.image});
    }   
}

void Factory::Render() {
    Color color;
    if (IsMouseHover()) {
        if (filled) {
            color = {50, 200, 50, 255};
        } else {
            color = {200, 200, 200, 255};
        }
    } else {
        color = {100, 100, 100, 255};
    }
    DrawRectanglePro(
        Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
        Vector2{ (float)-x, (float)-y }, rotation, color
    );

    for (Sprite& placedReactant : placedReactants) {
        DrawCircle(placedReactant.x, placedReactant.y, placedReactant.width/2, Color{200, 200, 200, 200});
        placedReactant.Render();
    }

    if (!filled)
        return;
    for (Sprite& pendingProduct : pendingProducts) {
        pendingProduct.Render();
    }
}

bool Factory::Place(string item) {
    for (Chemical& validReactant : validReactants) {
        if (item.compare(validReactant.name) == 0) {
            placedReactants.push_back({validReactant.image, validReactant.name});
            ReorgMyEquation();
            return true;
        }
    }
    return false;
}

void Factory::PopReactant(string reactant) {
    for (int i = 0; i < placedReactants.size(); i++) {
        if (placedReactants.at(i).name.compare(reactant) == 0) {
            if (i < placedReactants.size() - 1) {
                for (int j = i; j < placedReactants.size()-1; j++) {
                    placedReactants.at(j) = placedReactants.at(j+1);
                }
            }
            placedReactants.pop_back();
            return;
        }
    }
}

void Factory::ReorgMyEquation() {
    int longestFullfilledEquation = 0;
    for (Equation& equation : equations) {
        bool hasFullfilledEquation = true;
        for (Chemical& reactant : equation.reactants) {
            bool fullfilledReactant = false;
            for (Sprite& placedReactant : placedReactants) {
                if (reactant.name.compare(placedReactant.name) == 0) {
                    fullfilledReactant = true;
                    break;
                }
            }
            if (!fullfilledReactant) {
                hasFullfilledEquation = false;
                break;
            }
        }
        if (hasFullfilledEquation && equation.reactants.size() > longestFullfilledEquation) {
            longestFullfilledEquation = equation.reactants.size();
            fullfilledEquation = equation;
        }
    }
    pendingProducts.clear();
    if (longestFullfilledEquation == 0) {
        filled = false;
        fullfilledEquation.products.clear();
        fullfilledEquation.reactants.clear();
    } else {
        filled = true;
        int pWidth = 100;
        int py = y + height/2;
        for (int i = 0; i < fullfilledEquation.products.size(); i++) {
            int px = x - (fullfilledEquation.products.size() * pWidth/2) + i * pWidth + pWidth/2;
            pendingProducts.push_back({px, py, pWidth, pWidth, fullfilledEquation.products.at(i).image, fullfilledEquation.products.at(i).name});
        }
    }
    int rWidth = placedReactants.size() >= 3 ? 175 / placedReactants.size() : 64;
    float ry = y-height/2;
    for(int i = 0; i < placedReactants.size(); i++) {
        float rx = x - (placedReactants.size() * rWidth/2) + i * rWidth + rWidth/2;
        placedReactants.at(i).SetByState2D({rx, ry, rWidth, rWidth});
    }
}

Sprite Factory::DiscardListen() {
    for (Sprite placedReactant : placedReactants) {
        if (placedReactant.IsClicked()) {
            PopReactant(placedReactant.name);
            ReorgMyEquation();
            return placedReactant;
        }
    }
    return {"noitem"};
}

vector<Sprite> Factory::React() {
    vector<Sprite> ejectedProducts = pendingProducts;
    pendingProducts.clear();
    filled = false;
    for (Chemical reactant : fullfilledEquation.reactants)
        PopReactant(reactant.name);
    ReorgMyEquation();
    return ejectedProducts;
}