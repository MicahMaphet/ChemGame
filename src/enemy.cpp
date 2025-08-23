#include "raylib.h"
#include "enemy.h"
#include "util.h"
#include "cmath"

Enemy::Enemy(int x, int y, int width, int height) : Sprite(x, y, width, height) {
    maxSpeed = 5;
}

void Enemy::Render() {
    if (ShowBox)
        RenderBox();
    x += speedX;
    y += speedY;
    DrawCircle(x, y, width/2, RED);
}

void Enemy::SetTarget(Vector2 pose) {
    float angle = atan2(pose.y - y, pose.x - x);
    speedX = cos(angle) * maxSpeed;
    speedY = sin(angle) * maxSpeed;
}