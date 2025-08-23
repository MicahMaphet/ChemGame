#include "raylib.h"
#include "sprite.h"
#include "util.h"

class Enemy : public Sprite {
public:
    Enemy(int x, int y, int width, int height);
    Enemy(Vector2 pose, Dimentions dims);
    void Render();
    void SetTarget(Vector2 pose);
};