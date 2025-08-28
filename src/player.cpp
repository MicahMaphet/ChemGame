#include "player.h"
#include "raylib.h"
#include <cmath>
#include <iostream>

Player::Player() : Sprite(0, 0, 120, 180) {
    texture = LoadTexture("images/LuSuit.png");
    maxSpeed = 10;
    acceleration = 0.5;
}

void Player::KeyListen() {
    double speedXIncrease = 0, speedYIncrease = 0;

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
    } else if (!speedXIncrease && !speedYIncrease) {
        Deaccelerate();
    } else {
        speedX += speedXIncrease;
        speedY += speedYIncrease;
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
    if (ShowBox) Sprite::RenderBox();
    RenderImage(texture, 1.1);
    x += speedX;
    y += speedY;
    Hold();
}

void Player::Hold() {
    double angle = GetMouseAngle();
    double holdDistance = GetMouseDistance() < 130 ? GetMouseDistance() 
                          : sigmoid(GetMouseDistance() / 200) * 200;
    item.x = x + cos(angle) * holdDistance;
    item.y = y + sin(angle) * holdDistance;
    if (item.name.compare("noitem") != 0)
        item.RenderImage(item.image);
}

void Player::Deaccelerate() {
    speedX -= cos(heading) * abs(speedX) / 5;
    speedY -= sin(heading) * abs(speedY) / 5;
}


void Player::SelectItem(Sprite newItem) {
    item.name = newItem.name;
    item.image = newItem.image;
}