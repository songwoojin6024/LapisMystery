#pragma once
#include "GameManager.h"
#include "NPC.h"
#include "Opening.h"
#include <windows.h>
#include <iostream>
char getMoveKey();
void waitEnterOnly();

void interactWithNPC(NPC* npc, Player& p);
void runStory(GameState& state, Player& p);
void runWorldMap(GameState& state, Player& p, MapData& world, MapData& library, MapData& engineering, MapData& main_build);
void runLibrary(GameState& state, Player& p, MapData& library, NPC* libNpc);
void runEngineering(GameState& state, Player& p, MapData& engineering, NPC* engNpcs[]);
void runMainBuilding(GameState& state, Player& p, MapData& mainBuilding);