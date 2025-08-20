#include "factory.h"
#include <iostream>
#include <ctime>
using std::cout, std::time_t;

Factory::Factory(vector<string> ingredientsList) : Sprite(1500, 700, 100, 100) {
    filled = 0;
    for (string ingredient : ingredientsList) {
        ingredients.push_back(ingredient);
        ingredientStatuses.insert({ingredient, false});
    }
    timeFilled = 0;
}

void Factory::Render() {
    if (IsFilled() && time(NULL) - timeFilled > 5)
        return;

    unsigned char brightness = 100 + 155 * filled/ingredients.size();
    unsigned char alpha = timeFilled == 0 ? 255 : 255 * (5 - time(NULL) - timeFilled)/5;
    DrawRectanglePro(
        Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
        Vector2{ (float)-x, (float)-y }, rotation, Color{brightness, brightness, brightness, alpha}
    );
    DrawRectanglePro(
        Rectangle{ (float)0, (float)0, (float)(width*0.8*filled/ingredients.size()), (float)(height*0.1) },
        Vector2{ (float)(-x+0.4*width), (float)(-y-0.3*height) }, rotation, BLACK
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
            time(&timeFilled);
    }
}