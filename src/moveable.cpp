#include "moveable.h"
#include "raylib.h"

bool Moveable::IsTouching(Moveable moveable) {
    return moveable.x - moveable.width/2 < x + width/2 && moveable.x + moveable.width/2 > x - width/2 &&
           moveable.y - moveable.height/2 < y + height/2 && moveable.y + moveable.height/2 > y - height/2;
}

bool Moveable::MouseHover() {
    return GetMousePosition().x > x - width/2 && GetMousePosition().x < x + width/2 &&
           GetMousePosition().y > y - height/2 && GetMousePosition().y < y + height/2;
}

bool Moveable::Clicked() {
    return MouseHover() && IsMouseButtonReleased(0);
}

void Moveable::Render() {
    if (ShowBox)
        DrawRectangle(x - width/2, y - height/2, width, height, RED);
}

void Moveable::RenderImage(Texture2D image) {
    Rectangle srcRect = { 0.0f, 0.0f, (float)image.width, (float)image.height };
    Rectangle destRect = { (float)x, (float)y, (float)width, (float)height };
    DrawTexturePro(image, srcRect, destRect, (Vector2){(float)width/2, (float)height/2}, 0, WHITE);
}

Moveable::Moveable(int x, int y, int width, int height) : x(x), y(y), width(width), height(height),
    heading(0), speed(0), speedX(0), speedY(0), maxSpeed(0), speedDeadband(2), acceleration(0), ShowBox(false) {}

Moveable::Moveable() : Moveable(0, 0, 0, 0) {}