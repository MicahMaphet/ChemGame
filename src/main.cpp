#include <iostream>
#include "raylib.h"
#include "player.h"
#include "level.h"

int main(int, char**){
    std::cout << "Hello, from ChemGame!\n";
    InitWindow(2000, 1000, "ChemGame");
    SetWindowState(FLAG_VSYNC_HINT);

    Player player(0, 0, 100, 150);
    player.ShowBox = true;
    
    Level level;
    level.ShowBox = true;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        player.KeyListen();
        player.Render();
        level.Render();
        if (level.IsTouching(player))
            level.NextLevel();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
