#include <iostream>
#include "raylib.h"
#include "./moveable.h"

int main(int, char**){
    std::cout << "Hello, from cpp-game!\n";
    InitWindow(1000, 500, "Game");
    SetWindowState(FLAG_VSYNC_HINT);
    Moveable player;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        player.Render();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
