#pragma once

#include "sprite.h"
#include <vector>

using std::vector;

class Level : public Sprite {
private:
    Texture2D defaultImage;
public:
    Level();
    void Render();
    void NextLevel();
    int level;
    vector<State2D> positions;
};