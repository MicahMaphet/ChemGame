#include "factory.h"
#include <iostream>
using std::cout;

Factory::Factory(vector<ItemData> reactantsList, string productName) : Sprite(1500, 700, 125, 100) {
    filled = 0;
    for (ItemData reactant : reactantsList) {
        reactants.push_back(reactant);
        reactantStatuses.insert({reactant.name, false});
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
        Vector2{ (float)(-x+0.4*width), (float)(-y-0.3*height) }, rotation, {0, 255, 0, alpha}
    );
    int rWidth = reactants.size() >= 3 ? 150 / reactants.size() : 50;
    int ry = y-height/2;
    for(int i = 0; i < reactants.size(); i++) {
        int rx = x - (reactants.size() * rWidth/2) + i * rWidth + rWidth/2;
        bool activated = reactantStatuses.at(reactants.at(i).name);
        DrawCircle(rx, ry, rWidth/2*sqrt(2), activated ? Color{225, 225, 225, (unsigned char)(alpha*0.9)} : Color{200, 200, 200, (unsigned char)(alpha*0.7f)});
        Util::RenderImage(activated ? reactants.at(i).highlightedImage : reactants.at(i).image, rx, ry, rWidth, rWidth, 0, 1, alpha);
    }
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