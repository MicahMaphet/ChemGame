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
            color = {80, 140, 80, 255};
        } else {
            color = {200, 200, 200, 255};
        }
    } else {
        if (filled) {
            color = {90, 90, 140, 255};
        } else {
            color = {100, 100, 100, 255};
        }
    }
    DrawRectanglePro(
        Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
        Vector2{ (float)-x, (float)-y }, rotation, color
    );

    for (RSprite& placedReactant : placedReactants) {
        Color color;
        if (IsMouseHover()) {
            if (placedReactant.inEquation)
                color = {200, 240, 200, 225};
            else
                color = {225, 225, 225, 225};
        } else {
            if (placedReactant.inEquation)
                color = {150, 150, 220, 220};
            else
                color = {180, 180, 180, 200};
        }
        DrawCircle(placedReactant.x, placedReactant.y, placedReactant.width/2, color);
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
    filled = longestFullfilledEquation > 0;
    if (filled) {
        int pWidth = 72; // magic number (if you change it everything breaks)
        int py = y + height/2;
        for (int i = 0; i < fullfilledEquation.products.size(); i++) {
            int px = x - (fullfilledEquation.products.size() * pWidth/2) + i * pWidth + pWidth/2;
            pendingProducts.push_back({px, py, pWidth, pWidth, fullfilledEquation.products.at(i).image, fullfilledEquation.products.at(i).name});
        }
    } else {
        fullfilledEquation.products.clear();
        fullfilledEquation.reactants.clear();
    }

    vector<Chemical> claimedReactants = fullfilledEquation.reactants;
    int rWidth = placedReactants.size() >= 3 ? 175 / placedReactants.size() : 64;
    float ry = y-height/2;
    for(int i = 0; i < placedReactants.size(); i++) {
        RSprite& placedChem = placedReactants.at(i);
        float rx = x - (placedReactants.size() * rWidth/2) + i * rWidth + rWidth/2;
        placedChem.SetByState2D({rx, ry, rWidth, rWidth});
        placedChem.inEquation = false;
        // only runs if a fullfilled equation has been founded
        for (int j = 0; j < claimedReactants.size(); j++) {
            if (claimedReactants.at(j).name.compare(placedChem.name) == 0) {
                placedChem.inEquation = true;
                // this does not cause problems if claimedReactants has 1 or 0 elements, trust me
                for (int i = j; j < claimedReactants.size() - 1; j++)
                    claimedReactants.at(j) = claimedReactants.at(j+1);
                claimedReactants.pop_back();
                break;
            }
        }
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

RSprite::RSprite(Texture2D image, string name) : Sprite(image, name) {}