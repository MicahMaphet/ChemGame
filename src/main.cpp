#include <iostream>
#include "raylib.h"
#include "player.h"
#include "moveable.h"

int main(int, char**){
    std::cout << "Hello, from cpp-game!\n";
    InitWindow(1000, 500, "Game");
    SetWindowState(FLAG_VSYNC_HINT);
    Player player(0, 0, 100, 150);
    player.x = 0;
    player.y = 0;
    player.width = 100;
    player.height = 150;
    player.ShowBox = true;
    
    Moveable level(200, 200, 50, 50);
    level.ShowBox = true;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        player.KeyListen();
        player.Render();
        level.Render();
        if (level.IsTouching(player))
            break;
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
