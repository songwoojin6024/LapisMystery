#include "Game.h"
#include "Common.h"
#include "Maps.h"
#include <conio.h>
#include <limits>
#include"face1.h"
#include"face2.h"
#include"DialogueNPC.h"
#include "DialogueNPCData.h"
#include <windows.h>
#include <imm.h>
#pragma comment(lib, "imm32.lib")
using namespace std;

char getMoveKey() {
    static int heldKey = 0;
    static DWORD nextRepeatTime = 0;

    const DWORD FIRST_REPEAT_DELAY = 260;
    const DWORD VERTICAL_INTERVAL = 90;    // 위/아래 속도
    const DWORD HORIZONTAL_INTERVAL = 35;  // 왼쪽/오른쪽 속도

    while (true) {
        int currentKey = 0;
        char move = 0;
        DWORD repeatInterval = VERTICAL_INTERVAL;

        if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState(VK_UP) & 0x8000)) {
            currentKey = 'W';
            move = 'w';
            repeatInterval = VERTICAL_INTERVAL;
        }
        else if ((GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState(VK_DOWN) & 0x8000)) {
            currentKey = 'S';
            move = 's';
            repeatInterval = VERTICAL_INTERVAL;
        }
        else if ((GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000)) {
            currentKey = 'A';
            move = 'a';
            repeatInterval = HORIZONTAL_INTERVAL;
        }
        else if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
            currentKey = 'D';
            move = 'd';
            repeatInterval = HORIZONTAL_INTERVAL;
        }
        else if (GetAsyncKeyState('I') & 0x8000) {
            currentKey = 'I';
            move = 'i';
            repeatInterval = VERTICAL_INTERVAL;
        }

        DWORD now = GetTickCount();

        if (currentKey == 0) {
            heldKey = 0;
            nextRepeatTime = 0;
            Sleep(10);
            continue;
        }

        if (currentKey != heldKey) {
            heldKey = currentKey;
            nextRepeatTime = now + FIRST_REPEAT_DELAY;
            return move;
        }

        if (now >= nextRepeatTime) {
            nextRepeatTime = now + repeatInterval;
            return move;
        }

        Sleep(5);
    }
}
void waitEnterOnly() {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    while (true) {
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                Sleep(10);
            }
            break;
        }

        Sleep(10);
    }

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}
void addProgress(Player& p) {
    if (p.progress < p.maxProgress) {
        p.progress++;
    }
}
int getProgressPercent(const Player& p) {
    if (p.maxProgress <= 0) {
        return 0;
    }

    return (p.progress * 100) / p.maxProgress;
}