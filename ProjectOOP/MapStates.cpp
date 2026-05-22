#include "Game.h"
#include "Common.h"
#include "Maps.h"
#include "DialogueNPC.h"
#include "DialogueNPCData.h"
#include "InvestigationObjects.h"
#include <windows.h>
#include <iostream>

using namespace std;

void runWorldMap(GameState& state, Player& p, MapData& world, MapData& library, MapData& engineering, MapData& mainB) {
    renderGame(p, world);

    char move = getMoveKey();

    int nx = p.x, ny = p.y;
    if (move == 'w' || move == 72) { ny--; p.dir = UP; }
    else if (move == 's' || move == 80) { ny++; p.dir = DOWN; }
    else if (move == 'a' || move == 75) { nx--; p.dir = LEFT; }
    else if (move == 'd' || move == 77) { nx++; p.dir = RIGHT; }

    if (ny < 0 || ny >= 40 || nx < 0 || nx >= 120) return;

    char target = worldMap[ny][nx];

    if (target == ' ' || target == 'L' || target == 'B' || target == 'S' || target == 'G') {
        p.x = nx; p.y = ny;
    }
    if (target == 'L') {
        state = LIBRARY;
        p.x = 50; p.y = 3;
        system("cls");
        cout << "도서관에 입장합니다..." << endl;
        Sleep(500);
    }
    if (target == 'G') {
        state = ENGINEERING;
        p.x = 50; p.y = 3;
        system("cls");
        cout << "덕래관으로 입장합니다..." << endl;
        Sleep(500);
    }
    if (target == 'S') {
        state = ENGINEERING;
        p.x = 50; p.y = 3;
        system("cls");
        cout << "카페(상점)으로 입장합니다..." << endl;
        Sleep(500);
    }
    if (target == 'B') {
        state = MAIN_BUILDING;
        p.x = 64; p.y = 35;
        system("cls");
        cout << "본관으로 입장합니다..." << endl;
        Sleep(500);
    }
}

void runLibrary(GameState& state, Player& p, MapData& library, NPC* libNpc) {
    renderGame(p, library);

    char move = getMoveKey();

    int nx = p.x, ny = p.y;
    if (move == 'w' || move == 72) { ny--; p.dir = UP; }
    else if (move == 's' || move == 80) { ny++; p.dir = DOWN; }
    else if (move == 'a' || move == 75) { nx--; p.dir = LEFT; }
    else if (move == 'd' || move == 77) { nx++; p.dir = RIGHT; }

    if (ny < 0 || ny >= 40 || nx < 0 || nx >= 120) return;

    char target = libMap[ny][nx];

    if (target != '#') { p.x = nx; p.y = ny; }
    if (target == '&') { interactWithNPC(libNpc, p); p.y++; }
    if (target == '@') {showSearchRecord(p);p.y++;}
    if (target == '!') { showEmptyObject(); p.y++; }
    if (target == 'E') {
        state = WORLD_MAP;
        p.x = library.exitX;
        p.y = library.exitY;
        system("cls");
    }
}

void runEngineering(GameState& state, Player& p, MapData& engineering, NPC* engNpcs[]) {
    renderGame(p, engineering);

    char move = getMoveKey();

    int nx = p.x, ny = p.y;
    if (move == 'w' || move == 72) { ny--; p.dir = UP; }
    else if (move == 's' || move == 80) { ny++; p.dir = DOWN; }
    else if (move == 'a' || move == 75) { nx--; p.dir = LEFT; }
    else if (move == 'd' || move == 77) { nx++; p.dir = RIGHT; }

    if (ny < 0 || ny >= 40 || nx < 0 || nx >= 120) return;

    char target = engMap[ny][nx];

    if (target != '#') { p.x = nx; p.y = ny; }
    if (target == '!') { interactWithNPC(engNpcs[0], p); p.y++; }
    if (target == '@') { interactWithNPC(engNpcs[1], p); p.y++; }
    if (target == '%') { interactWithNPC(engNpcs[2], p); p.y++; }
    if (target == '$') { interactWithNPC(engNpcs[3], p); p.y++; }
    if (target == '&') { interactWithNPC(engNpcs[4], p); p.y++; }
    if (target == 'P') { runDialogueNPC(professorNpc, p); p.y++; }
    if (target == 'T') { runDialogueNPC(tiredStudentNpc, p); p.y++; }
    if (target == 'E') {
        state = WORLD_MAP;
        p.x = engineering.exitX;
        p.y = engineering.exitY;
        system("cls");
    }
}
void runMainBuilding(GameState& state, Player& p, MapData& mainBuilding) {
    renderGame(p, mainBuilding);

    char move = getMoveKey();

    int nx = p.x, ny = p.y;
    if (move == 'w' || move == 72) { ny--; p.dir = UP; }
    else if (move == 's' || move == 80) { ny++; p.dir = DOWN; }
    else if (move == 'a' || move == 75) { nx--; p.dir = LEFT; }
    else if (move == 'd' || move == 77) { nx++; p.dir = RIGHT; }

    if (ny < 0 || ny >= 40 || nx < 0 || nx >= 120) return;

    char target = mainBMap[ny][nx];

    if (target != '#') { p.x = nx; p.y = ny; }
    if (target == 'T') { runDialogueNPC(guardNpc, p); p.y++; }
    if (target == '?') {showScratchedFloor(p); p.y++;}
    if (target == 'E') {
        state = WORLD_MAP;
        p.x = mainBuilding.exitX;
        p.y = mainBuilding.exitY;
        system("cls");
    }
}