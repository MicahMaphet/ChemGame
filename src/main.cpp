#include <iostream>
#include <string.h>
#include "raylib.h"
#include "player.h"
#include "inventory.h"
#include "factory.h"
#include "item.h"
#include "explosion.h"
#include "enemy.h"
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
        {"images/Ethanol.png", "Ethanol"},
        {"images/Hg.png", "Mercury"},
        {"images/Hg(CNO)2.png", "Mercury Fulminate"},
        {"images/match.png", "Match"},
    };
    vector<string>itemNames;
    map<string, ItemData> items;
    for (ItemData item : itemVector) {
        items.insert({item.name, item});
        itemNames.push_back(item.name);
    }

    Player player(0, 0, 120, 180);
    player.SelectItem({items.at("Match").image, "Match"});
    
    Sprite door{1000, 200, 120, 40};
    door.image = LoadTexture("images/Door.png");
    int level = 0;


    Inventory inventory(800, 800);

    Factory factory;
    factory.AddEquation({items.at("Potasium Nitrate"), items.at("Carbon"), items.at("Sulfer")}, {items.at("Black Powder")});
    factory.AddEquation({items.at("Sulfuric Acid"), items.at("Nitric Acid"), items.at("Glycerol")},  {items.at("Nitroglycerin")});
    factory.AddEquation({items.at("Toluene"), items.at("Nitric Acid"), items.at("Sulfuric Acid")}, {items.at("Trinitrotoluene")});
    factory.AddEquation({items.at("Ethanol"), items.at("Mercury"), items.at("Nitric Acid")}, {items.at("Mercury Fulminate")});

    Sprite* spriteRefs[] = {(Sprite*)&player, (Sprite*)&door, (Sprite*)&factory};

    vector<map<Sprite*, PositionRotation>> levelLayout;
    /** A position must be set for the sprite to appear on the level */
    // Level 1
    levelLayout.push_back({
        {&player, {600, 500}},
        {&door, {1000, 500, 90}}
    });
    // Level 2
    levelLayout.push_back({ 
        {&player, {0, 0}},
        {&door, {500, 500, 90}},
        {&factory, {1000, 700}}
    });
    // Level 3
    levelLayout.push_back({ 
        {&player, {500, 500}},
        {&door, {1700, 500}},
        {&factory, {1000, 500}}
    });
    // Level 4
    levelLayout.push_back({ 
        {&player, {600, 200}},
        {&door, {1500, 700, 90}},
        {&factory, {200, 800}}
    });
    // Level 5;
    levelLayout.push_back({ 
        {&player, {100, 500}},
        {&door, {50, 500}}
    });

    // set up first level
    for (Sprite* ref : spriteRefs) {
        if (levelLayout.at(level).count(ref) != 0)
            (*ref).SetByPositionRotation(levelLayout.at(level).at(ref));
        else
            (*ref).SetByPose({-INFINITY, -INFINITY}); // is infinity a place...
    }
    level = 1;

    enum GameState {
        Moving,
        Inventory
    };
    GameState gameState = Moving;

    vector<Item> placedItems;
    vector<Explosion> activeExplosions;
    vector<Enemy> enemies;

    bool haltItemAction = false;
    while (!WindowShouldClose()) {
        haltItemAction = false;
        BeginDrawing();
        ClearBackground(BLACK);
        factory.Render();
        player.Render();
        door.RenderImage();
        for (int i = 0; i < placedItems.size(); i++) {
            if (haltItemAction) {
                break;
            }
            Item &item = placedItems.at(i);
            if (player.IsTouching(item)) {
                inventory.AddItem(item);
                placedItems.erase(placedItems.begin() + i);
                haltItemAction = true;
            } else if (item.IsClicked() && player.item.name.compare("noitem") == 0) {
                player.SelectItem(item);
                inventory.AddItem(item);
                inventory.SelectItem(item.name);
                placedItems.erase(placedItems.begin() + i);
                haltItemAction = true;
            } else if (IsMouseButtonReleased(0) && player.item.name.compare("Match") == 0 && item.IsTouching(player.item)) {
                for (string exName : {"Mercury Fulminate", "Nitroglycerin", "Black Powder", "Trinitrotoluene"}) {
                    if (item.name.compare(exName) == 0) {
                        activeExplosions.push_back({item.GetPosition(), 64, 5});
                        for (int j = i; j < placedItems.size() - 1; j++) {
                            placedItems.at(j) = placedItems.at(j+1);
                        }
                        placedItems.pop_back();
                        i = 0;
                        break;
                    }
                }
            }

            item.Render();
        }

        for (int i = 0; i < activeExplosions.size(); i++) {
            Explosion& explosion = activeExplosions.at(i);
            if (explosion.IsFinished()) {
                for (int j = i; j < activeExplosions.size() - 1; j++) {
                    activeExplosions.at(j) = activeExplosions.at(j+1);
                }
                activeExplosions.pop_back();
                i = 0; // this bad
            } else {
                for (int j = 0; j < enemies.size(); j++) {
                    Enemy& enemy = enemies.at(j);
                    if (enemy.IsTouching({explosion.x, explosion.y, explosion.radius*2, explosion.radius*2})) {
                        for (int k = j; k < enemies.size() - 1; k++) {
                            enemies.at(k) = enemies.at(k+1);
                        }
                        enemies.pop_back();
                        j = 0;
                    }
                }
                explosion.Render();
            }
        }
        if (haltItemAction) {
            EndDrawing();
            continue;
        }

        for (int i = 0; i < enemies.size(); i++) {
            Enemy& enemy = enemies.at(i);
            enemy.SetTarget(player.GetPosition());
            enemy.Render();
        }

        switch (gameState) {
        // I have enough indentation already
        case Moving: {
            player.KeyListen();
            if (factory.IsClicked() && factory.IsTouching(player.item) && factory.Place(player.item.name)) {
                inventory.PopItem(player.item.name);
                player.item.name = "noitem";
                break;
            }
            if (IsMouseButtonReleased(0) && player.item.name.compare("noitem") == 0) {
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
            if (IsKeyReleased(KEY_Q)) {
                for (string item_name : itemNames) {
                    if (player.item.name.compare(item_name) == 0) {
                        placedItems.push_back({player.item.GetPosition(), items.at(item_name)});
                        inventory.PopItem(item_name);
                        player.item.name = "noitem";
                    }
                }
            }

            if (IsKeyPressed(KEY_E))
                gameState = Inventory;
            break;
        }
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
                if (level >= levelLayout.size())
                    break;
                if (levelLayout.at(level - 1).count(ref) != 0) 
                    (*ref).SetByPositionRotation(levelLayout.at(level - 1).at(ref));
                else
                    (*ref).SetByPositionRotation({-INFINITY, -INFINITY});
            }
            switch (level) {
                case 2:
                placedItems.push_back({1000, 100, items.at("Sulfer")});
                placedItems.push_back({30, 200, items.at("Glycerol")});
                placedItems.push_back({300, 900, items.at("Potasium Nitrate")});
                placedItems.push_back({1500, 200, items.at("Sulfuric Acid")});
                placedItems.push_back({1500, 400, items.at("Nitric Acid")});
                placedItems.push_back({800, 400, items.at("Nitric Acid")});
                placedItems.push_back({150, 200, items.at("Nitric Acid")});
                placedItems.push_back({250, 200, items.at("Mercury Fulminate")});
                placedItems.push_back({700, 120, items.at("Ethanol")});
                placedItems.push_back({700, 200, items.at("Mercury")});
                enemies.push_back({1800, 800, 100, 100});
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
