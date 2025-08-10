#pragma once

#include "raylib.h"
#include "./moveable.h"

class Player: public Moveable {
public:
    void KeyListen();
};