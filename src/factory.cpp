#include "factory.h"
#include <iostream>
using std::cout;

Factory::Factory(vector<string> ingredientsList) : Sprite(1500, 700, 100, 100) {
    filled = 0;
    for (string ingredient : ingredientsList) {
        ingredients.push_back(ingredient);
        ingredientStatuses.insert({ingredient, false});
    }
    timeFilled = 0;
}

void Factory::Render() {
    if (IsFilled() && GetTime() - timeFilled > timeToFade)
        return;
    unsigned char brightness = 100 + 155 * filled/ingredients.size();
    unsigned char alpha = timeFilled == 0 ? 255 : 255 * (timeToFade - GetTime() + timeFilled)/timeToFade;
    if (alpha < 0) alpha = 0;
    DrawRectanglePro(
        Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
        Vector2{ (float)-x, (float)-y }, rotation, Color{brightness, brightness, brightness, alpha}
    );
    DrawRectanglePro(
        Rectangle{ (float)0, (float)0, (float)(width*0.8*filled/ingredients.size()), (float)(height*0.1) },
        Vector2{ (float)(-x+0.4*width), (float)(-y-0.3*height) }, rotation, {0, 0, 0, alpha}
    );
}

bool Factory::IsFilled() {
    return filled == ingredients.size();
}

void Factory::Place(string ingredient) {
    if (IsFilled()) return;
    if (!ingredientStatuses.at(ingredient)) {
        ingredientStatuses.at(ingredient) = true;
        filled++;
        if (IsFilled())
            timeFilled = GetTime();
    }
}