#include "sprite.h"
#include "raylib.h"

bool Sprite::IsTouching(Sprite sprite) {
    return sprite.x - sprite.width/2 < x + width/2 && sprite.x + sprite.width/2 > x - width/2 &&
           sprite.y - sprite.height/2 < y + height/2 && sprite.y + sprite.height/2 > y - height/2;
}

bool Sprite::MouseHover() {
    return GetMousePosition().x > x - width/2 && GetMousePosition().x < x + width/2 &&
           GetMousePosition().y > y - height/2 && GetMousePosition().y < y + height/2;
}

bool Sprite::Clicked() {
    return MouseHover() && IsMouseButtonReleased(0);
}

void Sprite::Render() {
    if (ShowBox)
        DrawRectangle(x - width/2, y - height/2, width, height, RED);
}

void Sprite::RenderImage(Texture2D image) {
    Rectangle srcRect = { 0.0f, 0.0f, (float)image.width, (float)image.height };
    Rectangle destRect = { (float)x, (float)y, (float)width, (float)height };
    DrawTexturePro(image, srcRect, destRect, (Vector2){(float)width/2, (float)height/2}, 0, WHITE);
}

Sprite::Sprite(int x, int y, int width, int height) : x(x), y(y), width(width), height(height),
    heading(0), speed(0), speedX(0), speedY(0), maxSpeed(0), speedDeadband(2), acceleration(0), ShowBox(false) {}

Sprite::Sprite() : Sprite(0, 0, 0, 0) {}

void Sprite::SetByPose(Position pose) {
    x = pose.x;
    y = pose.y;
}

void Sprite::SetByDims(Dimentions pose) {
    width = pose.width;
    height = pose.height;
}

void Sprite::SetByState2D(State2D state2D) {
    SetByPose(state2D.pose);
    SetByDims(state2D.dims);
}

void Sprite::State2D::Set(int x, int y, int width, int height) {
    pose.x = x;
    pose.y = y;
    dims.width = width;
    dims.height = height;
}