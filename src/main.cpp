#include <iostream>
#include <string.h>
#include "raylib.h"
#include "player.h"
#include "level.h"
#include "work_bench.h"
#include "inventory.h"
#include "blackpowder_factory.h"

int main(int, char**){
    std::cout << "Hello, from ChemGame!\n";
    InitWindow(2000, 1000, "ChemGame");
    SetWindowState(FLAG_VSYNC_HINT);

    Player player(0, 0, 120, 180);
    
    Level level;

    Sprite completeButton(GetScreenWidth() - 200, GetScreenHeight() - 200, 100, 100);

    struct CompleteButtonImages {
        Texture2D idle = LoadTexture("images/CompleteButton.png");
        Texture2D highlight = LoadTexture("images/CompleteButtonHighlight.png");
    };
    CompleteButtonImages completeButtonImages;


    WorkBench workBench(1000, 800, 175, 100);

    Inventory inventory(800, 800);

    BlackPowderFactory blackPowderFactory;

    enum GameState {
        Moving,
        Labing,
        Inventory
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
                if (workBench.IsClicked()) {
                    gameState = Labing;
                    workBench.Display();
                }
                if (IsKeyPressed(KEY_E))
                    gameState = Inventory;
                break;
            }
            case Labing: {
                if (completeButton.IsMouseHover()) {
                    completeButton.RenderImage(completeButtonImages.highlight);
                    if (IsMouseButtonReleased(0)) {
                        gameState = Moving;
                        workBench.EndDisplay();
                    }
                }
                else completeButton.RenderImage(completeButtonImages.idle);
                break;
            }
            case Inventory: {
                inventory.Render();
                player.itemImage = inventory.GetSelectedItemImage();
                player.item.name = inventory.GetSelectedItem().name;
                if (IsKeyPressed(KEY_E)) {
                    gameState = Moving;
                }
                break;
            }
        }

        if (gameState != Moving) {
            player.Deaccelerate();
        }

        if (level.IsTouching(player)) {
            level.NextLevel();
            player.x = 0;
            player.y = 0;
        }

        if (blackPowderFactory.IsTouching(player.item)) {
            std::cout << player.item.name << "\n";
            if (player.item.name.compare("KNO3") == 0) {
                blackPowderFactory.hasKNO3 = true;
            }
            else if (player.item.name.compare("C") == 0) {
                blackPowderFactory.hasC = true;
                std::cout << "carbon\n";
            }
            else if (player.item.name.compare("S") == 0)
                blackPowderFactory.hasS = true;
        }

        blackPowderFactory.Render();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
