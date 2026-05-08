#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
using namespace std;

class CardTile {
public:
    int  id;
    bool flipped;
    bool matched;
};

static const wchar_t* CARD_LABELS[8] = {
    L" SWJ ", L" JHC ", L" HHB ", L" BBS ",
    L" SIH ", L" PSH ", L" JSJ ", L" SWP "
};

// ── 유틸 ───────────────────────────────────────────────────────────────
static void cg_gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

static void cg_drawCard(int col, int row, const CardTile& card, bool isCursor) {
    const int BOARD_LEFT = 40, BOARD_TOP = 8, CARD_W = 8, CARD_H = 4;
    int x = BOARD_LEFT + col * CARD_W;
    int y = BOARD_TOP + row * CARD_H;

    wstring top = isCursor ? L"┏━━━━━┓" : L"┌─────┐";
    wstring bottom = isCursor ? L"┗━━━━━┛" : L"└─────┘";
    wstring side = isCursor ? L"┃" : L"│";

    cg_gotoxy(x, y);     wcout << top;
    cg_gotoxy(x, y + 1);
    if (card.matched)      wcout << side << L"  ✓  " << side;
    else if (card.flipped) wcout << side << CARD_LABELS[card.id] << side;
    else                   wcout << side << L"  ?  " << side;
    cg_gotoxy(x, y + 2);  wcout << bottom;
}

static void cg_drawBoard(const vector<CardTile>& board, int cursorPos,
    int firstPick, int tries, int matched) {
    const int BOARD_LEFT = 40, BOARD_TOP = 8, CARD_H = 4;

    cg_gotoxy(46, 2); wcout << L"◈━━━━━━━━━━━━━━━━━━━━━◈";
    cg_gotoxy(46, 3); wcout << L"┃  [ 용의자 카드 대조 ]┃";
    cg_gotoxy(46, 4); wcout << L"◈━━━━━━━━━━━━━━━━━━━━━◈";

    for (int i = 0; i < 16; ++i)
        cg_drawCard(i % 4, i / 4, board[i], i == cursorPos);

    cg_gotoxy(BOARD_LEFT, BOARD_TOP + 4 * CARD_H + 1);
    wcout << L"시도 횟수: " << tries << L"  |  매칭 완료: " << matched << L" / 8";

    cg_gotoxy(BOARD_LEFT, BOARD_TOP + 4 * CARD_H + 2);
    if (firstPick != -1)
        wcout << L"선택한 카드: [ " << CARD_LABELS[board[firstPick].id]
        << L" ]  두 번째 카드를 고르세요...    ";
    else
        wcout << L"                                                        ";

    cg_gotoxy(BOARD_LEFT, BOARD_TOP + 4 * CARD_H + 3);
    wcout << L"[ ↑↓←→ 이동 | Enter: 뒤집기 | ESC: 포기(실패) ]";
}

static void cg_showResult(int tries) {
    system("cls");
    cg_gotoxy(42, 15); wcout << L"◈━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◈";
    cg_gotoxy(42, 16); wcout << L"┃       모든 카드를 맞췄습니다!        ┃";
    cg_gotoxy(42, 17);
    wcout << L"┃   총 시도 횟수: " << tries;
    int pad = (tries < 10) ? 16 : 15;
    for (int i = 0; i < pad; ++i) wcout << L" ";
    wcout << L"┃";
    cg_gotoxy(42, 18); wcout << L"◈━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◈";
    cg_gotoxy(48, 20); wcout << L"[ 아무 키나 누르면 계속... ]";
    _getch();
}


// 성공 시 true, ESC 포기 시 false 반환
inline bool runCardGame() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    vector<CardTile> board(16);
    for (int i = 0; i < 16; ++i)
        board[i] = { i / 2, false, false };

    mt19937 rng((unsigned int)time(nullptr));
    shuffle(board.begin(), board.end(), rng);

    int cursorPos = 0, firstPick = -1, tries = 0, matchedCnt = 0;
    bool success = false;

    while (true) {
        system("cls");
        cg_drawBoard(board, cursorPos, firstPick, tries, matchedCnt);

        int input = _getch();
        if (input == 224 || input == 0) {
            input = _getch();
            int col = cursorPos % 4, row = cursorPos / 4;
            if (input == 72 && row > 0) cursorPos -= 4;
            if (input == 80 && row < 3) cursorPos += 4;
            if (input == 75 && col > 0) cursorPos -= 1;
            if (input == 77 && col < 3) cursorPos += 1;
        }
        else if (input == 13) {
            CardTile& cur = board[cursorPos];
            if (cur.matched || cur.flipped) continue;
            cur.flipped = true;

            if (firstPick == -1) {
                firstPick = cursorPos;
            }
            else {
                tries++;
                system("cls");
                cg_drawBoard(board, cursorPos, firstPick, tries, matchedCnt);
                Sleep(800);

                if (board[firstPick].id == cur.id) {
                    board[firstPick].matched = cur.matched = true;
                    matchedCnt++;
                    if (matchedCnt == 8) {
                        system("cls");
                        cg_drawBoard(board, cursorPos, -1, tries, matchedCnt);
                        Sleep(600);
                        cg_showResult(tries);
                        success = true;
                        break;
                    }
                }
                else {
                    board[firstPick].flipped = cur.flipped = false;
                }
                firstPick = -1;
            }
        }
        else if (input == 27) break; // ESC
    }

    _setmode(_fileno(stdout), _O_TEXT);
    system("cls");
    return success;
}
