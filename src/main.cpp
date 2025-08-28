#include <iostream>
#include <string.h>
#include <map>
#include "game.h" 

using std::map;
using std::cout;

int main(int, char**){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(2000, 1000, "ChemGame");

    Game game;

    bool haltItemAction = false;
    while (!WindowShouldClose()) {
        haltItemAction = false;
        BeginDrawing();
        ClearBackground(BLACK);
        game.Loop();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
