#include <iostream>
#include "raylib.h"
#include "player.h"
#include "level.h"
#include "work_bench.h"

int main(int, char**){
    std::cout << "Hello, from ChemGame!\n";
    InitWindow(2000, 1000, "ChemGame");
    SetWindowState(FLAG_VSYNC_HINT);

    Player player(0, 0, 84, 140);
    
    Level level;
    level.ShowBox = true;

    WorkBench workBench(1000, 800, 150, 100);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        player.KeyListen();
        player.Render();
        level.Render();
        workBench.Render();
        DrawText(TextFormat("Mouse %f %f", GetMousePosition().x, GetMousePosition().y), 150, 0, 20, BLACK);
        if (level.IsTouching(player)) {
            level.NextLevel();
            player.x = 0;
            player.y = 0;
        }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
