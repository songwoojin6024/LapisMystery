#include "Game.h"
#include "Common.h"
#include "Maps.h"
#include <conio.h>
#include <limits>
#include"face1.h"
#include"face2.h"
using namespace std;

void interactWithNPC(NPC* npc, Player& p) {
    system("cls");

    if (npc->isCleared()) {
        cout << "\n[" << npc->getName() << "]: 조용히 해, 공부 중이야." << endl;
        cout << "\n(아무 키나 누르면 돌아갑니다.)" << endl;
        while (_kbhit()) _getch();
        _getch();
        system("cls");
        return;
    }

    int tries = 0;
    bool success = false;

    while (tries < 3 && !success) {
        system("cls");
        npc->talk();
        cout << "\n(엔터를 눌러 게임 시작...)" << endl;
        _getch();

        if (npc->playGame()) {
            success = true;
        }
        else {
            tries++;
            if (tries < 3) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                cout << "\n[실패! 남은 도전 횟수: " << (3 - tries) << "번]" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                cout << "(아무 키나 누르면 재도전...)" << endl;
                while (_kbhit()) _getch();
                _getch();
            }
        }
    }

    system("cls");

    if (success) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "\n[성공!] " << npc->getName() << "이(가) 단서와 사례비를 주었습니다." << endl;
        cout << "단서: " << npc->getHint() << endl;
        cout << "120원을 획득했습니다!" << endl;
        p.hints.push_back(npc->getHint());
        p.money += 120;
        npc->setCleared();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\n[실패...] 3번 모두 틀렸습니다. " << npc->getName() << "이(가) 실망했습니다." << endl;
        p.hearts--;
        cout << "♥ 하트가 하나 줄었습니다! 남은 하트: ";
        for (int i = 0; i < p.hearts; i++) cout << "♥ ";
        for (int i = p.hearts; i < 3; i++) cout << "♡ ";
        cout << endl;
        npc->addFail();
        npc->setCleared();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    cout << "\n(아무 키나 누르면 돌아갑니다.)" << endl;
    while (_kbhit()) _getch();
    _getch();
    system("cls");
}

void runStory(GameState& state) {
    //playOpening();
    system("cls");

    const int FACE_HEIGHT = 18;
    const int DIALOGUE_OFFSET = 5;
    const int TEXT_SPEED = 70;
    const int DIALOGUE_WAIT = 1000;
    int frame = 0;

    string playerName = "탐정"; 

    auto playFrame = [&]() {
        gotoxy(0, 0);
        if (frame % 2 == 0) face1();
        else                 face2();
        frame++;
        };

    auto typeDialogue = [&](const string& text) {
        int y = FACE_HEIGHT + DIALOGUE_OFFSET;
        gotoxy(0, y);
        cout << string(100, ' ');

        string currentText;
        for (size_t i = 0; i < text.size();) {
            playFrame();
            unsigned char c = text[i];
            int charSize = 1;
            if ((c & 0xF0) == 0xE0) charSize = 3;
            else if ((c & 0xE0) == 0xC0) charSize = 2;
            else if ((c & 0xF8) == 0xF0) charSize = 4;

            currentText += text.substr(i, charSize);
            gotoxy(0, y);
            cout << currentText;
            i += charSize;
            Sleep(TEXT_SPEED);
        }
        gotoxy(0, 0);
        face2();// 대화 끝나면 입 다물기
        };

    // 1. 첫 대사
    typeDialogue("안녕하세요! 당신이 그 탐정이시군요.");
    Sleep(DIALOGUE_WAIT);

    // 2. 이름 질문
    typeDialogue("당신의 이름이 무엇입니까???");

    // 이름 입력 칸 만들기
    int inputY = FACE_HEIGHT + DIALOGUE_OFFSET + 2;
    gotoxy(0, inputY);
    cout << "이름 입력: ";

    // 콘솔에서 이름을 입력받을 때 커서가 보이도록 설정
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = true; // 커서 보이기
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    cin >> playerName; // 이름 입력받기
    cin.clear();
    cin.ignore(10000, '\n');
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    cursorInfo.bVisible = false; // 다시 커서 숨기기
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // 입력받은 줄 지우기
    gotoxy(0, inputY);
    cout << string(50, ' ');

    // 3. 이름 확인 대사
    typeDialogue("아, 당신의 이름은 " + playerName + "(이)군요!!");
    Sleep(DIALOGUE_WAIT);

    // 4. 나머지 대화 (playerName 활용 가능)
    string restDialogues[] = {
        "자, " + playerName + " 탐정님! 도난 당한 청금석을 되찾아 볼까요?",
        "사전에 조사 된 바에 따르면 용의자는 총 5명입니다.",
        "증거를 모아 범인을 찾아 보아요!",
    };
    /*string dialogues[] = {
        "안녕하세요! 당신이 그 탐정이시군요.",
        "도난 당한 청금석 되찾아 볼까요?",
        "사전에 조사 된 바에 따르면 용의자는 총 5명입니다.",
        "증거를 모아 범인을 찾아 보아요!",
    };
    */
    for (const string& d : restDialogues) {
        typeDialogue(d);
        Sleep(DIALOGUE_WAIT);
    }

    gotoxy(0, FACE_HEIGHT + DIALOGUE_OFFSET + 2);
    cout << ">> [ S ] 키를 눌러 캠퍼스로 나가기...";

    while (true)
    {
        if (GetAsyncKeyState('S') & 0x8000)
            break;

        Sleep(10);
    }

    // S 키에서 손 뗄 때까지 기다리기
    while (GetAsyncKeyState('S') & 0x8000)
    {
        Sleep(10);
    }

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    state = WORLD_MAP;
    return;
}

void runWorldMap(GameState& state, Player& p, MapData& world, MapData& library, MapData& engineering, MapData& mainB) {
    renderGame(p, world);

    char move = _getch();
    if (move == -32) move = _getch();

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

    char move = _getch();
    if (move == -32) move = _getch();

    int nx = p.x, ny = p.y;
    if (move == 'w' || move == 72) { ny--; p.dir = UP; }
    else if (move == 's' || move == 80) { ny++; p.dir = DOWN; }
    else if (move == 'a' || move == 75) { nx--; p.dir = LEFT; }
    else if (move == 'd' || move == 77) { nx++; p.dir = RIGHT; }

    if (ny < 0 || ny >= 40 || nx < 0 || nx >= 120) return;

    char target = libMap[ny][nx];

    if (target != '#') { p.x = nx; p.y = ny; }
    if (target == '&') { interactWithNPC(libNpc, p); p.y++; }
    if (target == 'E') {
        state = WORLD_MAP;
        p.x = library.exitX;
        p.y = library.exitY;
        system("cls");
    }
}

void runEngineering(GameState& state, Player& p, MapData& engineering, NPC* engNpcs[]) {
    renderGame(p, engineering);

    char move = _getch();
    if (move == -32) move = _getch();

    int nx = p.x, ny = p.y;
    if (move == 'w' || move == 72) { ny--; p.dir = UP; }
    else if (move == 's' || move == 80) { ny++; p.dir = DOWN; }
    else if (move == 'a' || move == 75) { nx--; p.dir = LEFT; }
    else if (move == 'd' || move == 77) { nx++; p.dir = RIGHT; }

    if (ny < 0 || ny >= 40 || nx < 0 || nx >= 120) return;

    char target = engMap[ny][nx];

    if (target != '#') { p.x = nx; p.y = ny; }
    if (target == '1') { interactWithNPC(engNpcs[0], p); p.y++; }
    if (target == '2') { interactWithNPC(engNpcs[1], p); p.y++; }
    if (target == '3') { interactWithNPC(engNpcs[2], p); p.y++; }
    if (target == '4') { interactWithNPC(engNpcs[3], p); p.y++; }
    if (target == '5') { interactWithNPC(engNpcs[4], p); p.y++; }
    if (target == 'E') {
        state = WORLD_MAP;
        p.x = engineering.exitX;
        p.y = engineering.exitY;
        system("cls");
    }
}
void runMainBuilding(GameState& state, Player& p, MapData& mainBuilding) {
    renderGame(p, mainBuilding);

    char move = _getch();
    if (move == -32) move = _getch();

    int nx = p.x, ny = p.y;
    if (move == 'w' || move == 72) { ny--; p.dir = UP; }
    else if (move == 's' || move == 80) { ny++; p.dir = DOWN; }
    else if (move == 'a' || move == 75) { nx--; p.dir = LEFT; }
    else if (move == 'd' || move == 77) { nx++; p.dir = RIGHT; }

    if (ny < 0 || ny >= 40 || nx < 0 || nx >= 120) return;

    char target = mainBMap[ny][nx];

    if (target != '#') { p.x = nx; p.y = ny; }
    if (target == 'E') {
        state = WORLD_MAP;
        p.x = mainBuilding.exitX;
        p.y = mainBuilding.exitY;
        system("cls");
    }
}