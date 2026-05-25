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
#include "GoodEnding.h"
using namespace std;

int main() {
	initConsole();
    GameState state = MAIN_MENU;
    Player p;
    p.inventory = {
        { 1, "[익명의 제보 서류]", "송우진의 신체 정보를 확인할 수 있습니다.", 1200, ItemType::FORCED_UNLOCK, 1, 0 },
        { 2, "[증거 분석용 돋보기]", "굳게 닫힌 비밀 질문을 해제합니다.", 1200, ItemType::FORCED_UNLOCK, 2, 0 },
        { 3, "[뇌물용 초콜릿]", "어려운 미니게임 1개를 패스하고 단서를 얻습니다.", 300, ItemType::MINIGAME_PASS, 0, 0 },
        { 4, "[레쓰비 캔커피]", "하트를 1개 회복합니다.", 50, ItemType::HP_RECOVER, 1, 0 },
        { 5, "[매점 핫도그]", "하트를 3개 회복합니다.", 120, ItemType::HP_RECOVER, 3, 0 },
        { 6, "[박카스D]", "하트를 전부 회복합니다.", 250, ItemType::HP_RECOVER, 999, 0 }
    };
    LibraryNPC libNpc;
    EngNPC1 engNpc1; EngNPC2 engNpc2; EngNPC3 engNpc3;
    EngNPC4 engNpc4; EngNPC5 engNpc5; EngNPC6 engNpc6;
	MAINBNPC mainBNpc;

    NPC* engNpcs[] = { &engNpc1, &engNpc2, &engNpc3, &engNpc4, &engNpc5, &engNpc6 };

    MapData world = { worldMap, "캠퍼스",    11, 0,  0 };
    MapData library = { libMap,   "도서관 내부", 11, 102, 7 };
    MapData engineering = { engMap,   "공과대학",   11, 99, 29 };
	MapData main_build = { mainBMap, "본관", 11, 33, 12 };
    MapData cafeMap = { nullptr, "카페", 11, 86, 28 };

    while (true) {
        if (p.hearts <= 0) {
            state = BAD_ENDING;
        }
        if (state == MAIN_MENU)       runMainMenu(state);
        else if (state == STORY)       runStory(state, p);
        else if (state == WORLD_MAP)   runWorldMap(state, p, world, library, engineering, main_build);
        else if (state == LIBRARY) runLibrary(state, p, library, &libNpc);
        else if (state == ENGINEERING) runEngineering(state, p, engineering, engNpcs);
        else if (state == CAFE) runCafe(state, p, cafeMap);
        else if (state == MAIN_BUILDING) runMainBuilding(state, p, main_build, &mainBNpc);
        else if (state == ENDING) {
            playGoodEnding();
            break;
        }
        else if (state == BAD_ENDING) {
            runBadEnding();
            break;
        }
    }
    return 0;
}