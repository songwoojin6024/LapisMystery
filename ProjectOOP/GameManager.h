#pragma once
#include <vector>
#include <string>

// 상점 아이템 종류
 enum class ItemType {
    FORCED_UNLOCK,
    MINIGAME_PASS,
    HP_RECOVER,
    RESET_TALK
};

 class Item {
 public:
     int id;
     std::string name;
     std::string description;
     int price;
     ItemType type;
     int value;
     int count;
 };
enum GameState { MAIN_MENU, STORY, WORLD_MAP, LIBRARY, ENGINEERING, CAFE, MAIN_BUILDING, ENDING, BAD_ENDING };
enum Direction { UP, DOWN, LEFT, RIGHT };

class Player {
public:
    std::string name = "탐정";
    int x = 5;
    int y = 23;
    int hearts = 3;
    int maxHearts = 5;
    Direction dir = DOWN;
    int money = 500;
    int progress = 0;
    int maxProgress = 19;
    std::vector<std::string> hints;
    std::vector<Item> inventory;
};

class MapData {
public:
    char (*mapArray)[400];
    std::string name;
    int playerColor;
    int exitX, exitY;
};

const int WORLD_H = 40;
const int WORLD_W = 121;
const int INT_H = 20;
const int INT_W = 61;
void runCafe(GameState& state, Player& p, MapData& cafeMapData);
void openInventory(Player& p);
