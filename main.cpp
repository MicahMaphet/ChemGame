#include <iostream>
#include "raylib.h"

int main(int, char**){
    std::cout << "Hello, from cpp-game!\n";
    InitWindow(1000, 500, "Game");
    SetWindowState(FLAG_VSYNC_HINT);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
