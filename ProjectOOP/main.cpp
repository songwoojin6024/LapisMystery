#include <iostream>
#include <conio.h>
#include <windows.h>
#include "GameManager.h"
#include "NPC.h"
#include "Maps.h"
#include "Common.h"
#include "Game.h"
#include "MainMenuState.h"
#include "opening.h"
#include "BadEnding.h"
#include "DialogueNPCData.h"
using namespace std;

int main() {
	initConsole();
    //system("mode con:cols=200 lines=50");
    GameState state = MAIN_MENU;
    Player p;
    LibraryNPC libNpc;
    EngNPC1 engNpc1; EngNPC2 engNpc2; EngNPC3 engNpc3;
    EngNPC4 engNpc4; EngNPC5 engNpc5;

    NPC* engNpcs[] = { &engNpc1, &engNpc2, &engNpc3, &engNpc4, &engNpc5 };

    MapData world = { worldMap, "캠퍼스",    11, 0,  0 };
    MapData library = { libMap,   "도서관 내부", 11, 102, 7 };
    MapData engineering = { engMap,   "공과대학",   11, 99, 29 };
	MapData main_build = { mainBMap, "본관", 11, 33, 12 };

    while (true) {
        if (p.hearts <= 0) {
            state = BAD_ENDING;
        }
        if (state == MAIN_MENU)       runMainMenu(state);
        else if (state == STORY)       runStory(state, p);
        else if (state == WORLD_MAP)   runWorldMap(state, p, world, library, engineering, main_build);
        else if (state == LIBRARY) runLibrary(state, p, library, &libNpc);
        else if (state == ENGINEERING) runEngineering(state, p, engineering, engNpcs);
        else if (state == MAIN_BUILDING) runMainBuilding(state, p, main_build);
        else if (state == ENDING) {
             system("cls");
             cout << "\n\n\n\t\t [엔딩] \n\n" << endl;
             cout << "\t 청금석을 되찾고 총장님께 돌아갔다." << endl;
             cout << "\t 총장님: '잘했어! 장학금은 다음 학기에 지급할게!'" << endl;
             cout << "\n\t >> 게임을 종료하려면 아무 키나 누르세요..." << endl;
             _getch();
             break;
		}
        else if (state == BAD_ENDING) {
            runBadEnding();
            break;
        }
    }
    return 0;
}