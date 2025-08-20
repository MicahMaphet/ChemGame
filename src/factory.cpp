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
}

void Factory::Render() {
    if (IsFilled())
        return;

    unsigned char brightness = 100 + 155 * filled/ingredients.size();
    DrawRectanglePro(
        Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
        Vector2{ (float)-x, (float)-y }, rotation, Color{brightness, brightness, brightness, 255}
    );
    DrawRectanglePro(
        Rectangle{ (float)0, (float)0, (float)(width*0.9*filled/ingredients.size()), (float)(height*0.1) },
        Vector2{ (float)(-x+0.4*width), (float)(-y-0.3*height) }, rotation, BLACK
    );
    
}

bool Factory::IsFilled() {
    return filled == ingredients.size();
}

void Factory::Place(string ingredient) {
    if (!ingredientStatuses.at(ingredient)) {
        ingredientStatuses.at(ingredient) = true;
        filled++;
    }
}