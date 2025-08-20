#include "factory.h"
#include <iostream>
using std::cout;

Factory::Factory(vector<string> ingredientsList, string productName) : Sprite(1500, 700, 100, 100) {
    filled = 0;
    for (string ingredient : ingredientsList) {
        reactants.push_back(ingredient);
        reactantStatuses.insert({ingredient, false});
    }
    product = productName;
    timeFilled = 0;
}

void Factory::Render() {
    if (IsFilled() && GetTime() - timeFilled > timeToFade)
        return;
    unsigned char brightness = 100 + 155 * filled/reactants.size();
    unsigned char alpha = timeFilled == 0 ? 255 : 255 * (timeToFade - GetTime() + timeFilled)/timeToFade;
    if (alpha < 0) alpha = 0;
    DrawRectanglePro(
        Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
        Vector2{ (float)-x, (float)-y }, rotation, Color{brightness, brightness, brightness, alpha}
    );
    DrawRectanglePro(
        Rectangle{ (float)0, (float)0, (float)(width*0.8*filled/reactants.size()), (float)(height*0.1) },
        Vector2{ (float)(-x+0.4*width), (float)(-y-0.3*height) }, rotation, {0, 0, 0, alpha}
    );
}

bool Factory::IsFilled() {
    return filled == reactants.size();
}

void Factory::Place(string reactant) {
    if (IsFilled()) return;
    if (!reactantStatuses.at(reactant)) {
        reactantStatuses.at(reactant) = true;
        filled++;
        if (IsFilled())
            timeFilled = GetTime();
    }
}