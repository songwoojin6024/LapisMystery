#include "Game.h"
#include "Common.h"
#include "Maps.h"
#include "DialogueNPC.h"
#include "DialogueNPCData.h"
#include "InvestigationObjects.h"
#include <windows.h>
#include "FinalDeduction.h"
#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;

bool hasPlayerHint(const Player& p, const string& hint) {
    for (const string& h : p.hints) {
        if (h == hint) return true;
    }
    return false;
}
int getMenuChoice(int maxChoice) {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    while (true) {
        int key = _getch();

        if (key == 224 || key == 0) {
            _getch();
            continue;
        }

        if (key == 27) { // ESC
            return 0;
        }

        if (key >= '1' && key <= '0' + maxChoice) {
            return key - '0';
        }
    }
}
void runWorldMap(GameState& state, Player& p, MapData& world, MapData& library, MapData& engineering, MapData& mainB) {
    renderGame(p, world);

    char move = getMoveKey();

    if (move == 'i' || move == 'I') {
        while (GetAsyncKeyState('I') & 0x8000) {
            Sleep(10);
        }
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        openInventory(p);
        Sleep(100);
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        return;
    }

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
        state = CAFE;
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

    if (move == 'i' || move == 'I') {
        while (GetAsyncKeyState('I') & 0x8000) {
            Sleep(10);
        }
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        openInventory(p);
        Sleep(100);
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        return;
    }

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

    if (move == 'i' || move == 'I') {
        while (GetAsyncKeyState('I') & 0x8000) {
            Sleep(10);
        }
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        openInventory(p);
        Sleep(100);
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        return;
    }

    int nx = p.x, ny = p.y;
    if (move == 'w' || move == 72) { ny--; p.dir = UP; }
    else if (move == 's' || move == 80) { ny++; p.dir = DOWN; }
    else if (move == 'a' || move == 75) { nx--; p.dir = LEFT; }
    else if (move == 'd' || move == 77) { nx++; p.dir = RIGHT; }

    if (ny < 0 || ny >= 40 || nx < 0 || nx >= 120) return;

    char target = engMap[ny][nx];

    if (target != '#' && target != '-' && target != '|') {p.x = nx; p.y = ny;}
    if (target == '!') { interactWithNPC(engNpcs[0], p); p.y++; }
    if (target == '@') { interactWithNPC(engNpcs[1], p); p.y++; }
    if (target == '%') { interactWithNPC(engNpcs[2], p); p.y++; }
    if (target == '$') { interactWithNPC(engNpcs[3], p); p.y++; }
    if (target == '&') { interactWithNPC(engNpcs[4], p); p.y++; }
    if (target == 'P') { runDialogueNPC(professorNpc, p); p.y++; }
    if (target == 'A') { interactWithNPC(engNpcs[5], p); p.y++; }
    if (target == 'T') { runDialogueNPC(tiredStudentNpc, p); p.y++; }
    if (target == 'W') {runDialogueNPC(songWoojinNpc, p); p.y++; }
    if (target == 'G') { showBloodyGlove(p); p.y++; }
    if (target == '*') { showpcsearch(p); p.y++; }
    if (target == '?') { showSearchanalysis(p); p.y++; }
    if (target == 'E') {
        state = WORLD_MAP;
        p.x = engineering.exitX;
        p.y = engineering.exitY;
        system("cls");
    }
}
void runMainBuilding(GameState& state, Player& p, MapData& mainBuilding, NPC* mainBNpc) {
    renderGame(p, mainBuilding);

    char move = getMoveKey();

    if (move == 'i' || move == 'I') {
        while (GetAsyncKeyState('I') & 0x8000) {
            Sleep(10);
        }
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        openInventory(p);
        Sleep(100);
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        return;
    }

    int nx = p.x, ny = p.y;
    if (move == 'w' || move == 72) { ny--; p.dir = UP; }
    else if (move == 's' || move == 80) { ny++; p.dir = DOWN; }
    else if (move == 'a' || move == 75) { nx--; p.dir = LEFT; }
    else if (move == 'd' || move == 77) { nx++; p.dir = RIGHT; }

    if (ny < 0 || ny >= 40 || nx < 0 || nx >= 120) return;

    char target = mainBMap[ny][nx];

    if (target != '#') { p.x = nx; p.y = ny; }
    if (target == 'G') { runDialogueNPC(guardNpc, p); p.y++; }
    if (target == '?') {showScratchedFloor(p); p.y++;}
    if (target == 'F') {interactWithNPC(mainBNpc, p); p.y++;}
    if (target == 'L') { showElectricLine(p); p.y++; }
    if (target == ';') {showMasterKey(p); p.y++;}
    if (target == 'C') { runFinalDeduction(state, p); p.y++; }
    if (target == 'E') {
        state = WORLD_MAP;
        p.x = mainBuilding.exitX;
        p.y = mainBuilding.exitY;
        system("cls");
    }
}
void runCafe(GameState& state, Player& p, MapData& cafeMapData) {
    static vector<Item> shopItems = {
        { 1, "[익명의 제보 서류]", "송우진의 신체 정보를 확인할 수 있습니다.", 900, ItemType::FORCED_UNLOCK, 1, 0 },
        { 2, "[증거 분석용 돋보기]", "교수의 방 분석하기.", 900, ItemType::FORCED_UNLOCK, 2, 0 },
        { 3, "[뇌물용 초콜릿]", "어려운 미니게임 1개를 패스하고 단서를 얻습니다.", 300, ItemType::MINIGAME_PASS, 0, 0 },
        { 4, "[레쓰비 캔커피]", "하트를 1개 회복합니다.", 50, ItemType::HP_RECOVER, 1, 0 },
        { 5, "[매점 핫도그]", "하트를 3개 회복합니다.", 120, ItemType::HP_RECOVER, 3, 0 },
        { 6, "[박카스D]", "하트를 전부 회복합니다.", 250, ItemType::HP_RECOVER, 999, 0 }
    };

    while (true) {
        for (auto& shopItem : shopItems) {
            shopItem.count = 0;
            for (const auto& invItem : p.inventory) {
                if (shopItem.id == invItem.id) {
                    shopItem.count = invItem.count;
                    break;
                }
            }
        }

        system("cls");
        cout << "==========================================================================================" << endl;
        cout << "                       [ 계 명 대 복 지 관  C A F E  &  매 점 상 점 ]                     " << endl;
        cout << "==========================================================================================" << endl;
        cout << "  * 보유 금액 : " << setw(5) << p.money << " 원     |     * 현재 하트 : " << p.hearts << " / " << p.maxHearts << " 개" << endl;
        cout << "------------------------------------------------------------------------------------------" << endl;
        cout << "  번호   아이템 이름             가격         보유량     효과 설명" << endl;
        cout << "------------------------------------------------------------------------------------------" << endl;

        for (size_t i = 0; i < shopItems.size(); i++) {
            cout << "  [" << i + 1 << "]  "
                << left << setw(22) << shopItems[i].name
                << right << setw(5) << shopItems[i].price << " 원"
                << setw(10) << shopItems[i].count << " 개      "
                << shopItems[i].description << endl;
        }

        cout << "------------------------------------------------------------------------------------------" << endl;
        cout << "  [ESC]  카페 나가기" << endl;
        cout << "==========================================================================================" << endl;
        cout << " >> 메뉴/아이템 번호를 입력하세요: ";

        int choice = getMenuChoice((int)shopItems.size());

        if (choice == 0) {
            state = WORLD_MAP;
            p.x = cafeMapData.exitX;
            p.y = cafeMapData.exitY;
            system("cls");
            break;
        }

        if (choice < 1 || choice > static_cast<int>(shopItems.size())) {
            cout << "\n[!] 잘못된 번호입니다." << endl;
            Sleep(800);
            continue;
        }

        Item& selectedItem = shopItems[choice - 1];

        string shoeHint = "송우진의 발 사이즈는 265mm이다.";

        if (selectedItem.id == 1 && (selectedItem.count > 0 || hasPlayerHint(p, shoeHint))) {
            cout << "\n[!] 이 제보 서류는 한 번만 구매할 수 있습니다." << endl;
            Sleep(1000);
            continue;
        }
        string powderHint = "교수의 방에서 청금석 가루가 발견되었다.";

        if (selectedItem.id == 2 && (selectedItem.count > 0 || hasPlayerHint(p, powderHint))) {
            cout << "\n[!] 이 돋보기는 한 번만 구매할 수 있습니다." << endl;
            Sleep(1000);
            continue;
        }
        if (p.money < selectedItem.price) {
            cout << "\n[!] 돈이 부족합니다." << endl;
            Sleep(1000);
            continue;
        }

        if (selectedItem.type == ItemType::HP_RECOVER) {
            if (p.hearts >= p.maxHearts) {
                cout << "\n[!] 이미 하트가 가득 차 있습니다." << endl;
                Sleep(1000);
                continue;
            }

            p.money -= selectedItem.price;
            if (selectedItem.value == 999) p.hearts = p.maxHearts;
            else {
                p.hearts += selectedItem.value;
                if (p.hearts > p.maxHearts) p.hearts = p.maxHearts;
            }

            cout << "\n[+] " << selectedItem.name << " 사용! 하트를 회복했습니다." << endl;
            Sleep(1000);
            continue;
        }

        p.money -= selectedItem.price;

        bool alreadyHave = false;
        for (auto& invItem : p.inventory) {
            if (invItem.id == selectedItem.id) {
                invItem.count++;
                alreadyHave = true;
                break;
            }
        }

        if (!alreadyHave) {
            Item newItem = selectedItem;
            newItem.count = 1;
            p.inventory.push_back(newItem);
        }

        cout << "\n[+] " << selectedItem.name << " 구매 완료!" << endl;
        Sleep(1000);
    }
}

void openInventory(Player& p) {
    while (true) {
        system("cls");
        cout << "==========================================================================================" << endl;
        cout << "                       [ 내  가 방  /  I N V E N T O R Y ]                                " << endl;
        cout << "==========================================================================================" << endl;
        cout << "  * 보유 금액 : " << p.money << " 원     |     * 현재 하트 : " << p.hearts << " / " << p.maxHearts << " 개" << endl;
        cout << "------------------------------------------------------------------------------------------" << endl;

        vector<Item*> activeItems;
        for (size_t i = 0; i < p.inventory.size(); i++) {
            if (p.inventory[i].count > 0) {
                activeItems.push_back(&p.inventory[i]);
            }
        }

        if (activeItems.empty()) {
            cout << "\n                  가방이 비어 있습니다. 카페에서 아이템을 구매해보세요.\n" << endl;
            cout << "  [ESC]  가방 닫기" << endl;
            cout << " >> ";

            int emptyChoice = getMenuChoice(0);
            if (emptyChoice == 0) break;
            continue;
        }

        cout << "  번호   아이템 이름             보유량     효과 설명" << endl;
        cout << "------------------------------------------------------------------------------------------" << endl;
        for (size_t i = 0; i < activeItems.size(); i++) {
            cout << "  [" << i + 1 << "]  "
                << left << setw(22) << activeItems[i]->name
                << right << setw(5) << activeItems[i]->count << " 개      "
                << activeItems[i]->description << endl;
        }

        cout << "------------------------------------------------------------------------------------------" << endl;
        cout << "  [ESC]  가방 닫기" << endl;
        cout << " >> 사용할 아이템 번호를 입력하세요: ";

        int choice = getMenuChoice((int)activeItems.size());

        if (choice == 0) break;

        if (choice < 1 || choice > static_cast<int>(activeItems.size())) {
            cout << "\n[!] 잘못된 번호입니다." << endl;
            Sleep(800);
            continue;
        }

        Item* selected = activeItems[choice - 1];
        if (selected->id == 1) {
            string shoeHint = "송우진의 발 사이즈는 265mm이다.";

            system("cls");

            cout << "\n\n\t[ 익명의 제보 서류 ]\n\n";
            cout << "\t서류에는 송우진의 신체 정보가 적혀 있다.\n\n";
            cout << "\t* 송우진의 발 사이즈는 265mm이다.\n";

            if (!hasPlayerHint(p, shoeHint)) {
                p.hints.push_back(shoeHint);
                addProgress(p);
                cout << "\n\t[단서가 추가되었습니다.] " << shoeHint << endl;
            }
            else {
                cout << "\n\t[이미 확인한 단서입니다.]" << endl;
            }

            selected->count--;

            cout << "\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

            while (true) {
                if (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
                    GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                    while (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
                        GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                        Sleep(10);
                    }
                    break;
                }
                Sleep(10);
            }

            continue;
        }
        if (selected->id == 2) {
            string powderHint = "교수의 방에서 청금석 가루가 발견되었다.";

            system("cls");

            cout << "\n\n\t[ 증거 분석용 돋보기 ]\n\n";
            cout << "\t돋보기로 교수의 방을 꼼꼼히 살펴보았다.\n\n";
            cout << "\t분석 결과, 교수의 방에서 청금석 가루 발견!\n";

            if (!hasPlayerHint(p, powderHint)) {
                p.hints.push_back(powderHint);
                addProgress(p);
                cout << "\n\t[단서가 추가되었습니다.] " << powderHint << endl;
            }
            else {
                cout << "\n\t[이미 확인한 단서입니다.]" << endl;
            }

            selected->count--;

            cout << "\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

            while (true) {
                if (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
                    GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                    while (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
                        GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                        Sleep(10);
                    }
                    break;
                }
                Sleep(10);
            }

            continue;
        }
        if (selected->type == ItemType::HP_RECOVER) {
            if (p.hearts >= p.maxHearts) {
                cout << "\n[!] 이미 하트가 가득 차 있습니다." << endl;
                Sleep(1000);
                continue;
            }

            selected->count--;
            if (selected->value == 999) p.hearts = p.maxHearts;
            else {
                p.hearts += selected->value;
                if (p.hearts > p.maxHearts) p.hearts = p.maxHearts;
            }

            cout << "\n[+] " << selected->name << " 사용! 하트를 회복했습니다." << endl;
            Sleep(1000);
        }
        else {
            cout << "\n[*] " << selected->name << "은(는) 보관 중입니다." << endl;

            if (selected->id == 3) {
                cout << "    게임 NPC와 대화할 때 사용할 수 있습니다." << endl;
            }
            else {
                cout << "    필요한 상황에서 사용할 수 있습니다." << endl;
            }

            Sleep(1500);
        }
    }
}