#include "sprite.h"
#include "raylib.h"
#include <cmath>

Sprite::Sprite(int x, int y, int width, int height) : x(x), y(y), width(width), height(height),
    heading(0), rotation(0), speed(0), speedX(0), speedY(0), maxSpeed(0), speedDeadband(2), acceleration(0), ShowBox(false) {}

Sprite::Sprite(int width, int height) : Sprite(0, 0, width, height) {}

Sprite::Sprite() : Sprite(0, 0, 0, 0) {}

bool Sprite::IsTouching(Sprite sprite) {
    return sprite.x - sprite.width/2 < x + width/2 && sprite.x + sprite.width/2 > x - width/2 &&
           sprite.y - sprite.height/2 < y + height/2 && sprite.y + sprite.height/2 > y - height/2;
}

bool Sprite::IsMouseHover() {
    return GetMouseX() > x - width/2 && GetMouseX() < x + width/2 &&
           GetMouseY() > y - height/2 && GetMouseY() < y + height/2;
}

bool Sprite::IsClicked() {
    return IsMouseHover() && IsMouseButtonReleased(0);
}

void Sprite::MouseDragListen() {
    if (IsMouseHover() && IsMouseButtonDown(0))
        SetByVector2(GetMousePosition());
}

double Sprite::GetMouseAngle() {
    return atan2(GetMouseY() - y, GetMouseX() - x);
}

double Sprite:: GetMouseDistance() {
    return hypot(GetMouseX() - x, GetMouseY() - y);
}

/** Sprite rendering default: draw hitbox if ShowBox is true */
void Sprite::Render() {
    if (ShowBox)
        DrawRectanglePro(
            Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
            Vector2{ (float)-x, (float)-y }, rotation, IsMouseHover() ? WHITE : RED
        );
}

void Sprite::RenderImage(Texture2D image, float scale) {
    Util::RenderImage(image, x, y, width, height, rotation, scale);
}

/** Set the x and y coardanites of the sprite via Position argument */
void Sprite::SetByPose(Position pose) {
    x = pose.x;
    y = pose.y;
}

/** Set the width and y of the sprite via Dimentions argument */
void Sprite::SetByDims(Dimentions pose) {
    width = pose.width;
    height = pose.height;
}

/** Set the x, y, width, height via State2D argument */
void Sprite::SetByState2D(State2D state2D) {
    SetByPose(state2D.pose);
    SetByDims(state2D.dims);
    rotation = state2D.rotation;
}

void Sprite::SetByVector2(Vector2 vector2) {
    x = vector2.x;
    y = vector2.y;
}