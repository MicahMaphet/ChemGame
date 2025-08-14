#include "blackpowder_factory.h"

BlackPowderFactory::BlackPowderFactory() : Sprite(1500, 700, 100, 100) {
    pickedUp = hasKNO3 = hasC = hasS = false;
    blackPowderImage = LoadTexture("images/BlackPowder.png");
    blackPowderHighlightedImage = LoadTexture("images/BlackPowderHighlighted.png");
}

void BlackPowderFactory::Render() {
    if (pickedUp)
        return;
    filled = hasKNO3 + hasC + hasS;
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
        default:
            RenderImage(IsMouseHover() ? blackPowderHighlightedImage : blackPowderImage);
        break;
    }
}