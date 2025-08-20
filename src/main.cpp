#include <iostream>
#include <string.h>
#include "raylib.h"
#include "player.h"
#include "work_bench.h"
#include "inventory.h"
#include "factory.h"
#include "item.h"
#include <map>
using std::map;
using std::cout;

int main(int, char**){
    InitWindow(2000, 1000, "ChemGame");
    SetWindowState(FLAG_VSYNC_HINT);

    map<string, ItemData> items{
        {"KNO3", {"images/KNO3.png", "KNO3"}},
        {"C", {"images/Carbon.png", "C"}},
        {"S", {"images/Sulfer.png", "S"}},
        {"blackpowder", {"images/BlackPowder.png", "blackpowder"}}
    };

    Player player(0, 0, 120, 180);
    
    Sprite door{1000, 200, 120, 40};
    door.image = LoadTexture("images/Door.png");
    int level = 0;

    Sprite completeButton(GetScreenWidth() - 200, GetScreenHeight() - 200, 100, 100);

    struct CompleteButtonImages {
        Texture2D idle = LoadTexture("images/CompleteButton.png");
        Texture2D highlight = LoadTexture("images/CompleteButtonHighlight.png");
    };
    CompleteButtonImages completeButtonImages;

    WorkBench workBench(1000, 800, 175, 100);

    Inventory inventory(800, 800);
    inventory.AddItem(items.at("KNO3"));

    Factory blackPowderFactory{{"KNO3", "C", "S"}};

    Sprite* spriteReferences[] = {(Sprite*)&player, (Sprite*)&door, (Sprite*)&workBench, (Sprite*)&blackPowderFactory};

    vector<map<Sprite*, Vector2>> levelPositions;
    vector<map<Sprite*, float>> levelRotations;
    /** A position must be set for the sprite to appear on the level */
    // Level 1
    levelPositions.push_back({
            {&player, {100, 100}},
            {&door, {1000, 500}}
    });
    levelRotations.push_back({
        {&door, 90}
    });
    // Level 2
    levelPositions.push_back({ 
        {&player, {0, 0}},
        {&door, {500, 500}},
        {&workBench, {1000, 700}}
    });
    levelRotations.push_back({
        {&door, 90}
    });
    // Level 3
    levelPositions.push_back({ 
        {&player, {500, 500}},
        {&door, {1700, 500}},
        {&blackPowderFactory, {1000, 500}}
    });
    levelRotations.push_back({
        {&door, 0}
    });
    // Level 4
    levelPositions.push_back({ 
        {&player, {600, 200}},
        {&door, {1500, 700}}
    });
    levelRotations.push_back({
        {&door, 90}
    });
    // Level 5;
    levelPositions.push_back({ 
        {&player, {100, 500}},
        {&door, {50, 500}}
    });
    levelRotations.push_back({
        {&door, 0}
    });

    // set up first level
    for (Sprite* ref : spriteReferences) {
        if (levelPositions.at(level).count(ref) != 0) {
            (*ref).SetByPose(levelPositions.at(level).at(ref));
            if (levelRotations.at(level).count(ref) != 0)
                (*ref).rotation = levelRotations.at(level).at(ref);
        }
        else
            (*ref).SetByPose({-INFINITY, -INFINITY});
    }
    level = 1;

    enum GameState {
        Moving,
        Labing,
        Inventory
    };
    GameState gameState = Moving;

    vector<Item> placedItems;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        blackPowderFactory.Render();
        player.Render();
        door.RenderImage();
        workBench.Render();
        for (int i = 0; i < placedItems.size(); i++) {
            Item &item = placedItems.at(i);
            if (item.IsMouseHover() && IsMouseButtonPressed(0)) {
                inventory.AddItem(item);
                placedItems.erase(placedItems.begin() + i);
            }
            item.Render();
        }
        switch (gameState) {
            case Moving:
                player.KeyListen();
                if (blackPowderFactory.IsTouching(player.item)) {
                    for (string ingredient : blackPowderFactory.ingredients) {
                        if (player.item.name.compare(ingredient) == 0) {
                            blackPowderFactory.Place(ingredient);
                            inventory.PopItem(ingredient);
                            player.item.name = "noitem";
                            if (blackPowderFactory.IsFilled())
                                placedItems.push_back({blackPowderFactory.GetPosition(), items.at("blackpowder")});
                        }
                    }
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

                if (workBench.IsClicked()) {
                    gameState = Labing;
                    workBench.Display();
                }
                if (IsKeyPressed(KEY_E))
                    gameState = Inventory;
                break;
            case Labing:
                if (completeButton.IsMouseHover()) {
                    completeButton.RenderImage(completeButtonImages.highlight);
                    if (IsMouseButtonReleased(0)) {
                        gameState = Moving;
                        workBench.EndDisplay();
                    }
                }
                else completeButton.RenderImage(completeButtonImages.idle);
                break;
            case Inventory:
                inventory.Render();
                player.SelectItem(inventory.GetSelectedItem());
                if (IsKeyPressed(KEY_E)) {
                    gameState = Moving;
                break;
            }
        }

        if (gameState != Moving) {
            player.Deaccelerate();
        }

        if (door.IsTouching(player)) {
            level++;
            cout << '\n' << level;
            placedItems.clear();
            for (Sprite* ref : spriteReferences) {
                if (level >= levelPositions.size())
                    break;
                if (levelPositions.at(level - 1).count(ref) != 0) {
                    (*ref).SetByPose(levelPositions.at(level - 1).at(ref));
                    if (levelRotations.at(level).count(ref) != 0)
                        (*ref).rotation = levelRotations.at(level).at(ref);
                } else {
                    (*ref).SetByPose({-INFINITY, -INFINITY});
                }
            }
            cout << std::endl;
            switch (level) {
                case 2:
                placedItems.push_back({1000, 700, items.at("S")});
                break;
                case 3:
                placedItems.push_back({500, 900, items.at("C")});
                break;
            }
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
