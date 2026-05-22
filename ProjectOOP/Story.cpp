#include "Game.h"
#include "Common.h"
#include "face1.h"
#include "face2.h"
#include <windows.h>
#include <iostream>
#include <limits>

using namespace std;

void runStory(GameState& state, Player& p) {
    playOpening();
    system("cls");

    const int FACE_X = 32;
    const int FACE_Y = 2;
    const int DIALOGUE_X = 24;

    const int FACE_HEIGHT = 18;
    const int DIALOGUE_OFFSET = 5;
    const int TEXT_SPEED = 70;
    const int DIALOGUE_WAIT = 1000;
    int frame = 0;

    string playerName = "탐정";

    auto playFrame = [&]() {
        if (frame % 2 == 0) face1(FACE_X, FACE_Y);
        else                 face2(FACE_X, FACE_Y);
        frame++;
        };

    auto typeDialogue = [&](const string& text) {
        int y = FACE_Y + FACE_HEIGHT + DIALOGUE_OFFSET;

        gotoxy(DIALOGUE_X, y);
        cout << string(90, ' ');

        string currentText;

        for (size_t i = 0; i < text.size();) {
            playFrame();

            unsigned char c = text[i];
            int charSize = 1;

            if ((c & 0xF0) == 0xE0) charSize = 3;
            else if ((c & 0xE0) == 0xC0) charSize = 2;
            else if ((c & 0xF8) == 0xF0) charSize = 4;

            currentText += text.substr(i, charSize);

            gotoxy(DIALOGUE_X, y);
            cout << currentText;

            i += charSize;
            Sleep(TEXT_SPEED);
        }

        face2(FACE_X, FACE_Y);
        };

    // 1. 첫 대사
    typeDialogue("안녕하세요! 당신이 그 탐정이시군요.");
    Sleep(DIALOGUE_WAIT);

    // 2. 이름 질문
    typeDialogue("당신의 이름이 무엇입니까???");

    // 이름 입력 칸 만들기
    int dialogueY = FACE_Y + FACE_HEIGHT + DIALOGUE_OFFSET;
    int inputY = dialogueY + 2;

    gotoxy(DIALOGUE_X, inputY);
    cout << string(90, ' ');
    gotoxy(DIALOGUE_X, inputY);
    cout << "이름 입력: ";

    // 콘솔에서 이름을 입력받을 때 커서가 보이도록 설정
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    cin >> playerName;
    p.name = playerName;
    cin.clear();
    cin.ignore(10000, '\n');
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // 입력받은 줄 지우기
    gotoxy(DIALOGUE_X, inputY);
    cout << string(90, ' ');

    // 3. 이름 확인 대사
    typeDialogue("아, 당신의 이름은 " + playerName + "(이)군요!!");
    Sleep(DIALOGUE_WAIT);

    // 4. 나머지 대화 (playerName 활용 가능)
    string restDialogues[] = {
        "자, " + playerName + " 탐정님! 도난 당한 청금석을 되찾아 볼까요?",
        "사전에 조사 된 바에 따르면 용의자는 총 5명입니다.",
        "증거를 모아 범인을 찾아 보아요!",
    };
    for (const string& d : restDialogues) {
        typeDialogue(d);
        Sleep(DIALOGUE_WAIT);
    }

    gotoxy(DIALOGUE_X, FACE_Y + FACE_HEIGHT + DIALOGUE_OFFSET + 2);
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