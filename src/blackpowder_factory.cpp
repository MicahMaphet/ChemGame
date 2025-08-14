#include "blackpowder_factory.h"

BlackPowderFactory::BlackPowderFactory() : Sprite(1500, 700, 200, 200) {
    hasKNO3 = hasC = hasS = false;
}

void BlackPowderFactory::Render() {
    int fill = hasKNO3 + hasC + hasS;
    Color color;
    switch (fill) {
        case 0: color = WHITE; break;  
        case 1: color = YELLOW; break;
        case 2: color = ORANGE; break;
        default: color = RED; break;
    }

    DrawRectanglePro(
        Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
        Vector2{ (float)-x, (float)-y }, rotation, color
    );
}