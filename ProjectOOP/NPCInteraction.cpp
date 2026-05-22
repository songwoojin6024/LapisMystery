#include "Game.h"
#include "Common.h"
#include <conio.h>
#include <windows.h>
#include <iostream>

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
        waitEnterOnly();

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