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
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(2000, 1000, "ChemGame");

    vector<ItemData>itemVector{
        {"images/Carbon.png", "Carbon"},
        {"images/Sulfer.png", "Sulfer"},
        {"images/KNO3.png", "Potasium Nitrate"},
        {"images/BlackPowder.png", "Black Powder"},
        {"images/Glycerol.png", "Glycerol"},
        {"images/HNO3.png", "Nitric Acid"},
        {"images/H2SO4.png", "Sulfuric Acid"},
        {"images/Default.png", "Nitroglycerin", "C3H5N3O"},
        {"images/TNT.png", "Trinitrotoluene"},
        {"images/Toluene.png", "Toluene"},
    };
    vector<string>itemNames;
    map<string, ItemData> items;
    for (ItemData item : itemVector) {
        items.insert({item.name, item});
        itemNames.push_back(item.name);
    }

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

    Factory factory;
    factory.AddEquation({items.at("Potasium Nitrate"), items.at("Carbon"), items.at("Sulfer")}, {items.at("Black Powder")});
    factory.AddEquation({items.at("Sulfuric Acid"), items.at("Nitric Acid"), items.at("Glycerol")},  {items.at("Nitroglycerin")});
    factory.AddEquation({items.at("Toluene"), items.at("Nitric Acid"), items.at("Sulfuric Acid")}, {items.at("Trinitrotoluene")});

    Sprite* spriteRefs[] = {(Sprite*)&player, (Sprite*)&door, (Sprite*)&workBench, (Sprite*)&factory};

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
        {&factory, {1000, 700}}
    });
    levelRotations.push_back({
        {&door, 90}
    });
    // Level 3
    levelPositions.push_back({ 
        {&player, {500, 500}},
        {&door, {1700, 500}},
        {&factory, {1000, 500}}
    });
    levelRotations.push_back({
        {&door, 0}
    });
    // Level 4
    levelPositions.push_back({ 
        {&player, {600, 200}},
        {&door, {1500, 700}},
        {&factory, {200, 800}}
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
    for (Sprite* ref : spriteRefs) {
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
        factory.Render();
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
        // I have enough indentation already
        case Moving: {
            player.KeyListen();
            if (factory.IsTouching(player.item) && factory.Place(player.item.name)) {
                inventory.PopItem(player.item.name);
                player.item.name = "noitem";
            }
            if (IsMouseButtonReleased(0)) {
                Sprite discard = factory.DiscardListen();
                if (discard.name.compare("noitem") != 0) {
                    placedItems.push_back({discard.x, discard.y-50, items.at(discard.name)});
                } else {
                    if (factory.IsMouseHover() && factory.filled) {
                        for (Sprite product : factory.React()) {
                            placedItems.push_back({product.x, product.y, items.at(product.name)});
                        }
                    }
                }
            }
            if (IsMouseButtonPressed(0)) {
                for (string item_name : itemNames) {
                    if (player.item.name.compare(item_name) == 0) {
                        placedItems.push_back({GetMousePosition(), items.at(item_name)});
                        inventory.PopItem(item_name);
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
        }
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
            }
            break;
        }

        if (gameState != Moving) {
            player.Deaccelerate();
        }

        if (door.IsTouching(player)) {
            level++;
            placedItems.clear();
            for (Sprite* ref : spriteRefs) {
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
            switch (level) {
                case 2:
                placedItems.push_back({1000, 100, items.at("Sulfer")});
                placedItems.push_back({30, 200, items.at("Glycerol")});
                placedItems.push_back({300, 900, items.at("Potasium Nitrate")});
                placedItems.push_back({1500, 200, items.at("Sulfuric Acid")});
                placedItems.push_back({1500, 400, items.at("Nitric Acid")});
                break;
                case 3:
                placedItems.push_back({500, 900, items.at("Carbon")});
                placedItems.push_back({300, 600, items.at("Potasium Nitrate")});
                placedItems.push_back({120, 100, items.at("Potasium Nitrate")});
                placedItems.push_back({600, 400, items.at("Nitric Acid")});
                break;
                case 4:
                placedItems.push_back({800, 300, items.at("Toluene")});
                placedItems.push_back({600, 400, items.at("Sulfuric Acid")});
                break;
            }
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
