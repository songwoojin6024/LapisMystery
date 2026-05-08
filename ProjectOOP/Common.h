#pragma once
#include <windows.h>
#include <iostream>
#include "GameManager.h"

// Utils
void gotoxy(int x, int y);

// Render
void renderGame(Player& p, MapData& m);

// Console √ ±‚»≠
void initConsole();