#include "factory.h"
#include <iostream>
using std::cout;

Factory::Factory() : Sprite(1500, 700, 125, 100) {
    timeFilled = 0;
}

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
    DrawRectanglePro(
        Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
        Vector2{ (float)-x, (float)-y }, rotation, GRAY
    );

    for (Sprite& placedReactant : placedReactants) {
        DrawCircle(placedReactant.x, placedReactant.y, placedReactant.width/2, Color{200, 200, 200, 200});
        placedReactant.Render();
    }

    if (!filled)
        return;
    int numProducts = fullfilledEquation.products.size();
    int pWidth = 50;
    int py = y+height/2;
    for (int i = 0; i < numProducts; i++) {
        int px = x - (numProducts * pWidth/2) + i * pWidth + pWidth/2;
        Util::RenderImage(fullfilledEquation.products.at(i).image, px, py, pWidth, pWidth);
    }
}

bool Factory::Place(string item) {
    for (Chemical& validReactant : validReactants) {
        if (item.compare(validReactant.name) == 0) {
            placedReactants.push_back({validReactant.image, validReactant.name});
            // Find not just an equation that has been fullfilled by all the placed reactants.
            // Find the longest, most specific equation that has been fullfilled by all the placed reactants.
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
                    filled = true;
                }
            }
            int rWidth = placedReactants.size() >= 3 ? 175 / placedReactants.size() : 64;
            float ry = y-height/2;
            for(int i = 0; i < placedReactants.size(); i++) {
                float rx = x - (placedReactants.size() * rWidth/2) + i * rWidth + rWidth/2;
                placedReactants.at(i).SetByState2D({rx, ry, rWidth, rWidth});
            }
            return true;
        }
    }
    return false;
}