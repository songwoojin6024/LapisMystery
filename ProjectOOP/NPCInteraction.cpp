#include "Game.h"
#include "Common.h"
#include <conio.h>
#include <windows.h>
#include <iostream>

using namespace std;

bool hasMiniGamePass(Player& p) {
    for (const auto& item : p.inventory) {
        if (item.id == 3 && item.count > 0) {
            return true;
        }
    }
    return false;
}

void useMiniGamePass(Player& p) {
    for (auto& item : p.inventory) {
        if (item.id == 3 && item.count > 0) {
            item.count--;
            return;
        }
    }
}

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

        bool roundSuccess = false;

        if (hasMiniGamePass(p)) {
            cout << "\n[뇌물용 초콜릿 보유 중]" << endl;
            cout << "[C] 초콜릿으로 미니게임 패스" << endl;
            cout << "[Enter] 그냥 게임 시작" << endl;

            while (true) {
                if (GetAsyncKeyState('C') & 0x8000) {
                    while (GetAsyncKeyState('C') & 0x8000) Sleep(10);

                    useMiniGamePass(p);
                    roundSuccess = true;

                    system("cls");
                    cout << "\n[패스 성공!] 뇌물용 초콜릿을 건네고 단서를 얻었습니다." << endl;
                    Sleep(1000);
                    break;
                }

                if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                    while (GetAsyncKeyState(VK_RETURN) & 0x8000) Sleep(10);

                    roundSuccess = npc->playGame();
                    break;
                }

                Sleep(10);
            }
        }
        else {
            cout << "\n(엔터를 눌러 게임 시작...)" << endl;
            waitEnterOnly();

            roundSuccess = npc->playGame();
        }

        if (roundSuccess) {
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
        cout << npc->getReward() << "원을 획득했습니다!" << endl;
        p.money += npc->getReward();
        p.hints.push_back(npc->getHint());
        addProgress(p);
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
        addProgress(p);
        npc->setCleared();

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    cout << "\n(Enter 또는 ESC를 누르면 돌아갑니다.)" << endl;
    while (_kbhit()) _getch();
    _getch();
    system("cls");
}