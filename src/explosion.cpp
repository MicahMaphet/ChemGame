#include "raylib.h"
#include "explosion.h"
#include "util.h"


Explosion::Explosion(int x, int y, int radius, float durration) 
: x(x), y(y), radius(radius), durration(durration) {
    start = GetTime();
}

Explosion::Explosion(Vector2 pose, int radius, float durration) : Explosion(pose.x, pose.y, radius, durration) {}

void Explosion::Render() {
    if ((int)((GetTime() - start)*3) % 2 == 0) {
        DrawCircle(x, y, radius, ORANGE);
    } else {
        DrawCircle(x, y, radius*0.8, ORANGE);
    }
}

bool Explosion::IsFinished() {
    return GetTime() - start > durration;
}