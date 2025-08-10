#include <iostream>
#include "raylib.h"
#include "./player.h"
#include "./level.h"

int main(int, char**){
    std::cout << "Hello, from cpp-game!\n";
    InitWindow(1000, 500, "Game");
    SetWindowState(FLAG_VSYNC_HINT);
    Player player;
    player.x = 0;
    player.y = 0;
    player.width = 100;
    player.height = 150;
    player.ShowBox = true;
    
    Level level;
    level.x = 200;
    level.y = 200;
    level.width = 50;
    level.height = 50;
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
