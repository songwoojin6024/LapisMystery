#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "GameManager.h"
#include "common.h"
using namespace std;

inline void runMainMenu(GameState& state) {
    _setmode(_fileno(stdout), _O_U16TEXT);

    const int LAPIS_X = 42, MYSTERY_X = 28, GEM_X = 47, BOX_X = 52;
    int menuCursor = 0;

    while (true) {
        system("cls");

        gotoxy(LAPIS_X, 3);  wcout << L" ██╗      █████╗ ██████╗ ██╗███████╗";
        gotoxy(LAPIS_X, 4);  wcout << L" ██║     ██╔══██╗██╔══██╗██║██╔════╝";
        gotoxy(LAPIS_X, 5);  wcout << L" ██║     ███████║██████╔╝██║███████╗";
        gotoxy(LAPIS_X, 6);  wcout << L" ██║     ██╔══██║██╔═══╝ ██║╚════██║";
        gotoxy(LAPIS_X, 7);  wcout << L" ███████╗██║  ██║██║     ██║███████║";
        gotoxy(LAPIS_X, 8);  wcout << L" ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝";

        gotoxy(MYSTERY_X, 10); wcout << L"███╗   ███╗██╗   ██╗███████╗████████╗███████╗██████╗ ██╗   ██╗";
        gotoxy(MYSTERY_X, 11); wcout << L"████╗ ████║╚██╗ ██╔╝██╔════╝╚══██╔══╝██╔════╝██╔══██╗╚██╗ ██╔╝";
        gotoxy(MYSTERY_X, 12); wcout << L"██╔████╔██║ ╚████╔╝ ███████╗   ██║   █████╗  ██████╔╝ ╚████╔╝ ";
        gotoxy(MYSTERY_X, 13); wcout << L"██║╚██╔╝██║  ╚██╔╝  ╚════██║   ██║   ██╔══╝  ██╔══██╗  ╚██╔╝  ";
        gotoxy(MYSTERY_X, 14); wcout << L"██║ ╚═╝ ██║   ██║   ███████║   ██║   ███████╗██║  ██║   ██║   ";
        gotoxy(MYSTERY_X, 15); wcout << L"╚═╝     ╚═╝   ╚═╝   ╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝   ╚═╝   ";

        gotoxy(GEM_X, 17); wcout << L"◈    ───    ◈    ───    ◈";

        vector<wstring> labels = { L"시작하기", L"종료" };
        vector<int> paddings = { 4, 8 };
        int startY = 22;

        for (int i = 0; i < (int)labels.size(); ++i) {
            gotoxy(BOX_X, startY + i * 3);
            if (menuCursor == i) {
                wcout << L"┏━━━━━━━━━━━━━━┓";
                gotoxy(BOX_X, startY + i * 3 + 1);
                wcout << L"┃ ◆ " << labels[i];
                for (int s = 0; s < paddings[i]; ++s) wcout << L" ";
                wcout << L"▶ ┃";
                gotoxy(BOX_X, startY + i * 3 + 2);
                wcout << L"┗━━━━━━━━━━━━━━┛";
            }
            else {
                wcout << L"┌──────────────┐";
                gotoxy(BOX_X, startY + i * 3 + 1);
                wcout << L"│ ◇ " << labels[i];
                for (int s = 0; s < paddings[i]; ++s) wcout << L" ";
                wcout << L"  │";
                gotoxy(BOX_X, startY + i * 3 + 2);
                wcout << L"└──────────────┘";
            }
        }

        gotoxy(41, startY + (int)labels.size() * 3 + 2);
        wcout << L"[ ↑ / ↓ 방향키로 이동 | Enter: 선택 ]";

        int input = _getch();
        if (input == 224) {
            input = _getch();
            if (input == 72) menuCursor = (menuCursor > 0) ? menuCursor - 1 : 0;
            if (input == 80) menuCursor = (menuCursor < 1) ? menuCursor + 1 : 1;
        }
        else if (input == 13) {
            if (menuCursor == 0) {
                // wcout → cout 전환
                _setmode(_fileno(stdout), _O_TEXT);
                state = STORY;
                return;
            }
            else if (menuCursor == 1) {
                exit(0);
            }
        }
    }
}