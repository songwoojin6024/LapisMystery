#pragma once
#include <vector>
#include <string>

enum GameState { MAIN_MENU, STORY, WORLD_MAP, LIBRARY, ENGINEERING, CAFE, MAIN_BUILDING, ENDING, BAD_ENDING };
enum Direction { UP, DOWN, LEFT, RIGHT };

class Player {
public:
    std::string name = "Å½Á¤";
    int x = 5;
    int y = 23;
    int hearts = 3;
    Direction dir = DOWN;
    int money = 500;
    int progress = 0;
    int maxProgress = 10;
    std::vector<std::string> hints;
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