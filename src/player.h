#pragma once

#include "raylib.h"
#include "./character.h"

class Player: public Character {
public:
    void KeyListen();
};