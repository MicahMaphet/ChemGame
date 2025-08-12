#include <iostream>
#include "raylib.h"
#include "player.h"
#include "level.h"
#include "work_bench.h"

int main(int, char**){
    std::cout << "Hello, from ChemGame!\n";
    InitWindow(2000, 1000, "ChemGame");
    SetWindowState(FLAG_VSYNC_HINT);

    Player player(0, 0, 120, 180);
    
    Level level;
    level.ShowBox = true;

    Sprite completeButton(GetScreenWidth() - 200, GetScreenHeight() - 200, 100, 100);

    struct CompleteButtonImages {
        Texture2D idle = LoadTexture("images/CompleteButton.png");
        Texture2D highlight = LoadTexture("images/CompleteButtonHighlight.png");
    };
    CompleteButtonImages completeButtonImages;


    WorkBench workBench(1000, 800, 150, 100);

    enum GameState {
        Moving,
        Labing
    };
    GameState gameState = Moving;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        player.Render();
        level.Render();
        workBench.Render();
        switch (gameState) {
            case Moving: {
                player.KeyListen();
                if (workBench.Clicked()) {
                    gameState = Labing;
                    workBench.Display();
                }
                break;
            }
            case Labing: {
                if (completeButton.MouseHover()) {
                    completeButton.RenderImage(completeButtonImages.highlight);
                    if (IsMouseButtonReleased(0)) {
                        gameState = Moving;
                        workBench.EndDisplay();
                    }
                }
                else completeButton.RenderImage(completeButtonImages.idle);
                break;
            }
        }
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
