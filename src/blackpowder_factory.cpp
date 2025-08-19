#include "blackpowder_factory.h"

BlackPowderFactory::BlackPowderFactory() : Sprite(1500, 700, 100, 100) {
    filled = 0;
    for (auto x : ingredientStatuses)
        ingredients.push_back(x.first);

    blackPowderImage = LoadTexture("images/BlackPowder.png");
}

void BlackPowderFactory::Render() {
    if (IsFilled())
        return;

    switch (filled) {
        case 0:
            DrawRectanglePro(
                Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
                Vector2{ (float)-x, (float)-y }, rotation, WHITE
            );
        break;  
        case 1:
            DrawRectanglePro(
                Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
                Vector2{ (float)-x, (float)-y }, rotation, YELLOW
            );
        break;
        case 2:
            DrawRectanglePro(
                Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
                Vector2{ (float)-x, (float)-y }, rotation, RED
            );
        break;
    }
}

bool BlackPowderFactory::IsFilled() {
    return filled == ingredients.size();
}

void BlackPowderFactory::Place(string ingredient) {
    if (!ingredientStatuses.at(ingredient)) {
        ingredientStatuses.at(ingredient) = true;
        filled++;
    }
}