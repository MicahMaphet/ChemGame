#include "player.h"

void Player::KeyListen() {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        x -= 1;
    }

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        y -= 1;
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        y += 1;
    }

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        x += 1;
    }
}
