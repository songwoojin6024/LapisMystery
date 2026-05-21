#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

inline void badEndingGotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

inline void badEndingLine(int x, int y, const string& text, int delay = 45) {
    badEndingGotoxy(x, y);

    for (char ch : text) {
        cout << ch;
        Sleep(delay);
    }
}

inline void runBadEnding() {
    system("cls");

    int x = 18;
    int y = 10;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

    badEndingLine(x, y++, "단서를 찾기 위해 밤새 캠퍼스를 뛰어다니던 당신.");
    Sleep(700);

    badEndingLine(x, y++, "심장이 멎을 듯한 피로감이 몰려오며 바닥에 쓰러진다.");
    Sleep(1200);

    y++;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    badEndingLine(x, y++, "지나가던 공대생 1: \"어? 저기 사람 쓰러져 있는데요?\"");
    Sleep(800);

    badEndingLine(x, y++, "지나가던 공대생 2: \"쉿, 건들지 마. 딱 봐도 밤샘 과제 하다가 잠깐 자는 거잖아.\"");
    Sleep(1200);

    y++;

    badEndingLine(x, y++, "모두가 당신을 '그저 과제에 찌들어 자는 학생'으로 생각하고 무심히 지나친다.");
    Sleep(900);

    badEndingLine(x, y++, "결국 청금석은커녕 다음 날 아침 9시 전공 수업 출석마저 결석 처리되어 F학점을 맞이하게 된다.");
    Sleep(900);

    badEndingLine(x, y++, "교수님의 메일이 도착했다: \"자네, 이번 학기는 힘들겠군.\"");
    Sleep(1400);

    y++;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    badEndingLine(x, y++, "[ GAME OVER: F학점과 함께 강제 퇴장당했습니다. ]", 60);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    y += 2;
    badEndingLine(x, y, ">> 아무 키나 누르면 게임을 종료합니다...", 20);
    _getch();
}