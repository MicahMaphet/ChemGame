#include "raylib.h"
#include "util.h"

class Explosion {
public:
    Explosion(int x, int y, int radius, float durration);
    Explosion(Vector2 pose, int radius, float durration);
    bool IsFinished();
    void Render();
    int x = 0, y = 0;
    int radius;
    float start;
    float durration;
};