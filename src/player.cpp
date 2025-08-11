#include "player.h"
#include "raylib.h"
#include <cmath>

Player::Player(int x, int y, int width, int height) : Moveable(x, y, width, height) {
    texture = LoadTexture("images/WalterWhiteCat.png");
    maxSpeed = 10;
    acceleration = 0.5;
}

void Player::KeyListen() {
    double speedXIncrease, speedYIncrease = 0;

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        speedXIncrease = -acceleration;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        speedXIncrease = acceleration;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        speedYIncrease = -acceleration;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        speedYIncrease = acceleration;

    if (speedXIncrease && speedYIncrease) {
        speedXIncrease /= sqrt(2);
        speedYIncrease /= sqrt(2);
    }
    // if no input was provided and speed speed is essentially 0, just stop moving
    if (speed < speedDeadband && !speedXIncrease && !speedYIncrease) {
        speedX = speedY = 0;
    } else {
        if (!speedXIncrease)
             speedX -= cos(heading) * abs(speedX) / 5;
        else speedX += speedXIncrease;
        
        if (!speedYIncrease)
             speedY -= sin(heading) * abs(speedY) / 5;
        else speedY += speedYIncrease;

    }
    speed = hypot(speedX, speedY);
    heading = atan2(speedY, speedX);

    if (speed > maxSpeed) {
        speedX = cos(heading) * maxSpeed;
        speedY = sin(heading) * maxSpeed;
        speed = maxSpeed;
    }
}

void Player::Render() {
    Moveable::Render();
    RenderImage(texture);
    x += speedX;
    y += speedY;
}
