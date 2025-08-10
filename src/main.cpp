#include <iostream>
#include "raylib.h"
#include "./moveable.h"
#include "./player.h"

int main(int, char**){
    std::cout << "Hello, from cpp-game!\n";
    InitWindow(1000, 500, "Game");
    SetWindowState(FLAG_VSYNC_HINT);
    Player player;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        player.KeyListen();
        player.Render();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
