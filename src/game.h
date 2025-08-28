#include "iostream"
#include "raylib.h"
#include "sprite.h"
#include "player.h"
#include "inventory.h"
#include "explosion.h"
#include "util.h"
#include "factory.h"
#include "enemy.h"

class Game {
private:
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

public:
    Player player;
    Factory factory;
    Sprite door;
    Sprite* spriteRefs[3] = {(Sprite*)&player, (Sprite*)&door, (Sprite*)&factory};

    Inventory inventory;
    
    vector<string>itemNames;
    map<string, ItemData> items;

    vector<Item> placedItems;
    vector<Explosion> activeExplosions;
    vector<Enemy> enemies;

    int level;
    vector<map<Sprite*, PositionRotation>> levelLayout;
    Game();
    void Loop();
    void NextLevel();

    enum GameState {
        Moving,
        UsingInventory
    };
    GameState gameState = Moving;

};