#pragma once

#include "moveable.h"
#include <vector>

using std::vector;

class Level : public Moveable {
public:
    Level();
    void NextLevel();
    int level;
    vector<State2D> positions;
};