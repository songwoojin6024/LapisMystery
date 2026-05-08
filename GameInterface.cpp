/*#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
using namespace std;

void gotoxy(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void clearScreen() { system("cls"); }

void initConsole()
{
    system("mode con cols=120 lines=40");
    HWND console = GetConsoleWindow();
    LONG style = GetWindowLong(console, GWL_STYLE);
    style &= ~WS_SIZEBOX;
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(console, GWL_STYLE, style);
    SetWindowPos(console, NULL, 0, 0, 0, 0,
        SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
    CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ── 레이아웃 상수 ────────────────────────────────────────
// 전체: 120 x 40
// 메인:  x 0~79  (80칸)  사이드: x 80~119 (40칸)
// 씬:    y 0~23  (24줄)
// 대사:  y 24~39 (16줄)

const int MAIN_W = 80;
const int SIDE_X = 80;
const int SCENE_H = 24;
const int DIALOG_Y = 24;
const int TOTAL_H = 40;

// ── 가로선 그리기 헬퍼 ──────────────────────────────────
void hline(int x, int y, int len,
    wchar_t left, wchar_t mid, wchar_t right)
{
    gotoxy(x, y);
    wcout << left;
    for (int i = 0; i < len - 2; ++i) wcout << mid;
    wcout << right;
}

void fillRow(int x, int y, int len)
{
    gotoxy(x, y);
    wcout << L"║";
    for (int i = 0; i < len - 2; ++i) wcout << L" ";
    wcout << L"║";
}

// ── 씬 영역 ─────────────────────────────────────────────
void drawScene(const wstring& sceneName, const wstring& npcName)
{
    // 외곽 테두리
    hline(0, 0, MAIN_W, L'╔', L'═', L'╗');
    for (int y = 1; y < SCENE_H - 1; ++y) fillRow(0, y, MAIN_W);
    hline(0, SCENE_H - 1, MAIN_W, L'╚', L'═', L'╝');

    // 씬 이름
    gotoxy(3, 1);
    wcout << L"◈ " << sceneName << L" ◈";

    // NPC 박스 (중앙 배치)
    int npcX = 22, npcY = 5;
    hline(npcX, npcY, 36, L'┌', L'─', L'┐');
    for (int y = npcY + 1; y < npcY + 11; ++y) fillRow(npcX, y, 36);
    hline(npcX, npcY + 11, 36, L'└', L'─', L'┘');

    // NPC 텍스트
    gotoxy(npcX + 10, npcY + 4);
    wcout << L"( NPC 이미지 )";
    gotoxy(npcX + 2, npcY + 7);
    wcout << L"▶ " << npcName;
}

// ── 대사 영역 ────────────────────────────────────────────
void drawDialog(
    const wstring& speaker,
    const wstring& dialog,
    const vector<wstring>& choices,
    int choiceCursor)
{
    hline(0, DIALOG_Y, MAIN_W, L'╔', L'═', L'╗');
    for (int y = DIALOG_Y + 1; y < TOTAL_H - 1; ++y) fillRow(0, y, MAIN_W);
    hline(0, TOTAL_H - 1, MAIN_W, L'╚', L'═', L'╝');

    // 화자 + 대사
    gotoxy(3, DIALOG_Y + 1);
    wcout << L"[ " << speaker << L" ]";
    gotoxy(3, DIALOG_Y + 2);
    wcout << L"\"" << dialog << L"\"";

    // 구분선
    hline(1, DIALOG_Y + 4, MAIN_W - 2, L'├', L'─', L'┤');

    // 선택지
    for (int i = 0; i < (int)choices.size(); ++i)
    {
        gotoxy(4, DIALOG_Y + 5 + i * 2);
        wcout << (i == choiceCursor ? L"▶  " : L"   ");
        wcout << choices[i];
    }

    // 하단 안내
    hline(1, TOTAL_H - 2, MAIN_W - 2, L'├', L'─', L'┤');
    gotoxy(3, TOTAL_H - 1);
    wcout << L"╚";
    //gotoxy(4, TOTAL_H - 1);
    //wcout << L" ↑↓: 이동  Enter: 선택  H: 단서목록 ";
    gotoxy(MAIN_W - 1, TOTAL_H - 1);
    wcout << L"╝";
}

// ── 사이드바 ─────────────────────────────────────────────
void drawSidebar(
    const wstring& playerName,
    const wstring& location,
    const vector<wstring>& items,
    const vector<wstring>& hints,
    int lives,
    int hintCursor,
    bool hintOpen)
{
    const int W = 39; // 사이드 내부 너비 (SIDE_X+1 ~ 119)

    auto sline = [&](int y, wchar_t l, wchar_t m, wchar_t r) {
        gotoxy(SIDE_X, y); wcout << l;
        for (int i = 0; i < W - 2; ++i) wcout << m;
        wcout << r;
        };
    auto srow = [&](int y) {
        gotoxy(SIDE_X, y); wcout << L"║";
        for (int i = 0; i < W - 2; ++i) wcout << L" ";
        wcout << L"║";
        };
    auto stext = [&](int y, const wstring& t) {
        gotoxy(SIDE_X + 2, y); wcout << t;
        };

    // ┌ 플레이어 정보 (y 0~8) ──────────────────────────────
    sline(0, L'╔', L'═', L'╗');
    srow(1);  stext(1, L"[ 탐정 정보 ]");
    sline(2, L'╠', L'═', L'╣');
    srow(3);
    gotoxy(SIDE_X + 2, 3);
    wcout << L"이름 : " << playerName;
    srow(4);
    gotoxy(SIDE_X + 2, 4);
    wcout << L"위치 : " << location;
    sline(5, L'╠', L'═', L'╣');
    srow(6);
    gotoxy(SIDE_X + 2, 6);
    wcout << L"목숨 : ";
    for (int i = 0; i < 5; ++i)
        wcout << (i < lives ? L"♥ " : L"♡ ");
    sline(7, L'╚', L'═', L'╝');

    // ┌ 인벤토리 (y 9~18) ────────────────────────────────
    sline(9, L'╔', L'═', L'╗');
    srow(10); stext(10, L"[ 인벤토리 ]");
    sline(11, L'╠', L'═', L'╣');
    for (int i = 0; i < 4; ++i)
    {
        srow(12 + i);
        gotoxy(SIDE_X + 2, 12 + i);
        if (i < (int)items.size())
            wcout << L"◆ " << items[i];
        else
            wcout << L"· (없음)";
    }
    sline(16, L'╚', L'═', L'╝');

    // ┌ 단서 목록 (y 18~39) ──────────────────────────────
    sline(18, L'╔', L'═', L'╗');
    srow(19);
    gotoxy(SIDE_X + 2, 19);
    wcout << L"[ 단서 목록 ]  " << hints.size() << L"/9";
    sline(20, L'╠', L'═', L'╣');

    if (!hintOpen)
    {
        // 단서 목록만 표시
        for (int i = 0; i < 9; ++i)
        {
            if (20 + 1 + i >= TOTAL_H - 2) break;
            srow(21 + i);
            gotoxy(SIDE_X + 2, 21 + i);
            if (i < (int)hints.size())
                wcout << (i == hintCursor ? L"▶ " : L"  ") << hints[i];
            else
                wcout << L"  · (미발견)";
        }
        for (int y = 21 + 9; y < TOTAL_H - 2; ++y) srow(y);
        sline(TOTAL_H - 2, L'╠', L'═', L'╣');
        srow(TOTAL_H - 1);
        gotoxy(SIDE_X + 2, TOTAL_H - 1);
        wcout << L"H: 열기  ↑↓: 이동";
        // 마지막 줄은 열려있지 않으니 ╝로 닫기
        gotoxy(SIDE_X, TOTAL_H - 1); wcout << L"║";
        gotoxy(SIDE_X + W - 1, TOTAL_H - 1); wcout << L"║";
        sline(TOTAL_H, L'╚', L'═', L'╝'); // 실제론 39가 마지막
    }
    else
    {
        // 선택한 단서 상세 보기
        srow(21);
        gotoxy(SIDE_X + 2, 21);
        wcout << L"▶ " << hints[hintCursor];
        sline(22, L'╠', L'═', L'╣');
        srow(23); stext(23, L"[ 단서 상세 ]");
        srow(24); stext(24, L"현장에서 발견된 증거물.");
        srow(25); stext(25, L"수사에 참고하십시오.");
        for (int y = 26; y < TOTAL_H - 2; ++y) srow(y);
        sline(TOTAL_H - 2, L'╠', L'═', L'╣');
        srow(TOTAL_H - 1);
        gotoxy(SIDE_X + 2, TOTAL_H - 1);
        wcout << L"H: 닫기  ↑↓: 이동";
        gotoxy(SIDE_X, TOTAL_H - 1); wcout << L"║";
        gotoxy(SIDE_X + W - 1, TOTAL_H - 1); wcout << L"║";
        sline(TOTAL_H, L'╚', L'═', L'╝');
    }
}

// ── 메인 ────────────────────────────────────────────────
int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    initConsole();

    wstring playerName = L"[Name]";
    wstring location = L"덕래관 4층";
    vector<wstring> items = { L"찢어진 전공책", L"돌 부스러기" };
    vector<wstring> hints = { L"깨진 유리창", L"낯선 발자국", L"지워진 문서" };
    int lives = 4;
    int hintCursor = 0;
    bool hintOpen = false;
    int choiceCursor = 0;

    wstring sceneName = L"어두운 강의실 안";
    wstring npcName = L"수상한 교수님";
    wstring speaker = L"교수 제갈현철";
    wstring dialog = L"...당신이 [Name]학생이군요. 청금석은 어젯밤부터 보이지 않습니다.";
    vector<wstring> choices = {
        L"1. 교수님이 마지막으로 있던 곳이 어디죠?",
        L"2. 어젯밤 몇 시에 마지막으로 봤나요?",
        L"3. 청금석을 본 적 있나요?"
    };

    bool running = true;
    while (running)
    {
        clearScreen();
        drawScene(sceneName, npcName);
        drawDialog(speaker, dialog, choices, choiceCursor);
        drawSidebar(playerName, location, items, hints,
            lives, hintCursor, hintOpen);

        int input = _getch();
        if (input == 224 || input == 0)
        {
            input = _getch();
            if (!hintOpen)
            {
                if (input == 72) choiceCursor = max(0, choiceCursor - 1);
                if (input == 80) choiceCursor = min((int)choices.size() - 1,
                    choiceCursor + 1);
            }
            else
            {
                if (input == 72) hintCursor = max(0, hintCursor - 1);
                if (input == 80) hintCursor = min((int)hints.size() - 1,
                    hintCursor + 1);
            }
        }
        else if (input == 'h' || input == 'H')
        {
            hintOpen = !hintOpen;
        }
        else if (input == 13)
        {
            speaker = L"나";
            dialog = choices[choiceCursor];
        }
        else if (input == 27)
        {
            running = false;
        }
    } 

    return 0;
}*/