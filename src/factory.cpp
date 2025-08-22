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

    int rWidth = placedReactants.size() >= 3 ? 150 / placedReactants.size() : 50;
    int ry = y-height/2;
    for(int i = 0; i < placedReactants.size(); i++) {
        int rx = x - (placedReactants.size() * rWidth/2) + i * rWidth + rWidth/2;
        DrawCircle(rx, ry, rWidth/2*sqrt(2), Color{225, 225, 225, 200});
        Util::RenderImage(placedReactants.at(i).image, rx, ry, rWidth, rWidth);
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
            placedReactants.push_back(validReactant);
            // Find not just an equation that has been fullfilled by all the placed reactants.
            // Find the longest, most specific equation that has been fullfilled by all the placed reactants.
            int longestFullfilledEquation = 0;
            for (Equation& equation : equations) {
                bool hasFullfilledEquation = true;
                for (Chemical& reactant : equation.reactants) {
                    bool fullfilledReactant = false;
                    for (Chemical& placedReactant : placedReactants) {
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
            return true;
        }
    }
    return false;
}