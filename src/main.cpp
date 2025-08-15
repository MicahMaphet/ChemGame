#include <iostream>
#include <string.h>
#include "raylib.h"
#include "player.h"
#include "level.h"
#include "work_bench.h"
#include "inventory.h"
#include "blackpowder_factory.h"
#include "item.h"
#include <map>
using std::map;
using std::cout;

int main(int, char**){
    std::cout << "Hello, from ChemGame!\n";
    InitWindow(2000, 1000, "ChemGame");
    SetWindowState(FLAG_VSYNC_HINT);

    map<string, ItemData> items{
        {"KNO3", {"images/KNO3.png", "KNO3"}},
        {"C", {"images/Carbon.png", "C"}},
        {"S", {"images/Sulfer.png", "S"}},
        {"blackpowder", {"images/BlackPowder.png", "blackpowder"}}
    };

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
    inventory.AddItem({200, 200, LoadTexture("images/KNO3.png"), "KNO3"});
    inventory.AddItem({100, 100, LoadTexture("images/Carbon.png"), "C"});

    BlackPowderFactory blackPowderFactory;

    enum GameState {
        Moving,
        Labing,
        Inventory
    };
    GameState gameState = Moving;

    vector<Item> placedItems;
    placedItems.push_back({700, 400, items.at("S")});

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        blackPowderFactory.Render();
        player.Render();
        level.Render();
        workBench.Render();
        for (int i = 0; i < placedItems.size(); i++) {
            Item &item = placedItems.at(i);
            if (item.IsMouseHover() && IsMouseButtonPressed(0)) {
                inventory.AddItem({item.width, item.height, item.image, item.name});
                placedItems.erase(placedItems.begin() + i);
            }
            item.Render();
        }
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
                player.item.image = inventory.GetSelectedItem().image;
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
            if (player.item.name.compare("KNO3") == 0) {
                blackPowderFactory.hasKNO3 = true;
                inventory.PopItem("KNO3");
                player.item.name = "noitem";
            } else if (player.item.name.compare("C") == 0) {
                blackPowderFactory.hasC = true;
                inventory.PopItem("C");
                player.item.name = "noitem";
            } else if (player.item.name.compare("S") == 0) {
                blackPowderFactory.hasS = true;
                inventory.PopItem("S");
                player.item.name = "noitem";
            }
        }
        if (blackPowderFactory.IsClicked() && !blackPowderFactory.pickedUp && blackPowderFactory.filled == 3) {
            inventory.AddItem({100, 100, blackPowderFactory.blackPowderImage, "blackpowder"});
            blackPowderFactory.pickedUp = true;
        }
        if (IsMouseButtonPressed(0)) {
            for (string name : {"blackpowder", "S", "C", "KNO3"}) {
                if (player.item.name.compare(name) == 0) {
                    placedItems.push_back({GetMousePosition(), items.at(name)});
                    inventory.PopItem(name);
                    player.item.name = "noitem";
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
