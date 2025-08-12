#pragma once

#include "sprite.h"
#include <vector>

using std::vector;

class Level : public Sprite {
public:
    Level();
    void NextLevel();
    int level;
    vector<State2D> positions;
};