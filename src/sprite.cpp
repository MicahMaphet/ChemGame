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

void Sprite::MouseDragListen() {
    if (MouseHover() && IsMouseButtonDown(0))
        SetByVector2(GetMousePosition());
}

/** Sprite rendering default: draw hitbox if ShowBox is true */
void Sprite::Render() {
    if (ShowBox)
        DrawRectanglePro(
            Rectangle{ (float)-width/2, (float)-height/2, (float)width, (float)height },
            Vector2{ (float)-x, (float)-y }, rotation, MouseHover() ? WHITE : RED
        );
}

void Sprite::RenderImage(Texture2D image, float scale) {
    DrawTexturePro(image, 
        // initial dimentions of the circle as a rectangle
        Rectangle{ 0.0f, 0.0f, (float)image.width, (float)image.height }, 
        // final position and dimentions of the image
        Rectangle{ (float)x, (float)y, (float)width*scale, (float)height*scale },
        // define the origin of the image to be the center
        Vector2{(float)width*scale/2, (float)height*scale/2}, 
        rotation, WHITE
    );
}

Sprite::Sprite(int x, int y, int width, int height) : x(x), y(y), width(width), height(height),
    heading(0), rotation(0), speed(0), speedX(0), speedY(0), maxSpeed(0), speedDeadband(2), acceleration(0), ShowBox(false) {}

Sprite::Sprite() : Sprite(0, 0, 0, 0) {}

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

void State2D::Set(int x, int y, int width, int height, float rot) {
    pose.x = x;
    pose.y = y;
    dims.width = width;
    dims.height = height;
    rotation = rot;
}