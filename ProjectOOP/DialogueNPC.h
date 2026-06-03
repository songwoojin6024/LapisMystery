#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "GameManager.h"
#include "Game.h"

using namespace std;

void addProgress(Player& p);
class DialogueChoice {
public:
    wstring question;
    wstring answer;
};

class DialogueNPCData {
public:
    wstring sceneName;
    wstring npcName;
    wstring speaker;
    wstring location;
    vector<wstring> image;
    vector<DialogueChoice> choices;
    bool cleared = false;
};

enum DialogueInput {
    DN_NONE,
    DN_UP,
    DN_DOWN,
    DN_ENTER,
    DN_ESC
};

inline wstring dnToWide(const string& text) {
    if (text.empty()) return L"";

    int size = MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, NULL, 0);
    if (size <= 1) return L"";

    wstring result(size - 1, L'\0');
    MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, &result[0], size);
    return result;
}

inline wstring dnShortHint(const string& hint) {
    wstring text = dnToWide(hint);

    const int MAX_LEN = 12;

    if ((int)text.length() > MAX_LEN) {
        return text.substr(0, MAX_LEN) + L"...";
    }

    return text;
}

inline void dnWaitReleasedInputKeys() {
    while ((GetAsyncKeyState(VK_UP) & 0x8000) ||
        (GetAsyncKeyState(VK_DOWN) & 0x8000) ||
        (GetAsyncKeyState(VK_RETURN) & 0x8000) ||
        (GetAsyncKeyState(VK_ESCAPE) & 0x8000) ||
        (GetAsyncKeyState('W') & 0x8000) ||
        (GetAsyncKeyState('S') & 0x8000) ||
        (GetAsyncKeyState('A') & 0x8000) ||
        (GetAsyncKeyState('D') & 0x8000)) {
        Sleep(10);
    }

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

inline DialogueInput dnGetInput() {
    while (true) {
        if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000)) {
            while ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000)) Sleep(10);
            return DN_UP;
        }
        if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000)) {
            while ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000)) Sleep(10);
            return DN_DOWN;
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            while (GetAsyncKeyState(VK_RETURN) & 0x8000) Sleep(10);
            return DN_ENTER;
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            while (GetAsyncKeyState(VK_ESCAPE) & 0x8000) Sleep(10);
            return DN_ESC;
        }

        Sleep(10);
    }
}

inline void dnGotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

inline void dnHline(int x, int y, int len, wchar_t left, wchar_t mid, wchar_t right) {
    dnGotoxy(x, y);
    wcout << left;
    for (int i = 0; i < len - 2; i++) wcout << mid;
    wcout << right;
}

inline void dnEmptyRow(int x, int y, int len) {
    dnGotoxy(x, y);
    wcout << L"║";
    for (int i = 0; i < len - 2; i++) wcout << L" ";
    wcout << L"║";
}

inline void dnDrawScene(const DialogueNPCData& npc) {
    const int MAIN_W = 80;
    const int SCENE_H = 24;

    dnHline(0, 0, MAIN_W, L'╔', L'═', L'╗');
    for (int y = 1; y < SCENE_H - 1; y++) dnEmptyRow(0, y, MAIN_W);
    dnHline(0, SCENE_H - 1, MAIN_W, L'╚', L'═', L'╝');

    dnGotoxy(3, 1);
    wcout << L"◈ " << npc.sceneName << L" ◈";

    int imgX = 23;
    int imgY = 4;

    for (int i = 0; i < (int)npc.image.size(); i++) {
        dnGotoxy(imgX, imgY + i);
        wcout << npc.image[i];
    }

    dnGotoxy(30, 20);
    wcout << L"▶ " << npc.npcName;
}

inline void dnDrawDialog(const DialogueNPCData& npc, const wstring& currentDialog, int choiceCursor) {
    const int MAIN_W = 80;
    const int DIALOG_Y = 24;
    const int TOTAL_H = 40;

    dnHline(0, DIALOG_Y, MAIN_W, L'╔', L'═', L'╗');
    for (int y = DIALOG_Y + 1; y < TOTAL_H - 1; y++) dnEmptyRow(0, y, MAIN_W);
    dnHline(0, TOTAL_H - 1, MAIN_W, L'╚', L'═', L'╝');

    dnGotoxy(3, DIALOG_Y + 1);
    wcout << L"[ " << npc.speaker << L" ]";

    const int DIALOG_MAX_LEN = 34;
    wstring firstLine = currentDialog;
    wstring secondLine = L"";

    if ((int)currentDialog.length() > DIALOG_MAX_LEN) {
        firstLine = currentDialog.substr(0, DIALOG_MAX_LEN);
        secondLine = currentDialog.substr(DIALOG_MAX_LEN);
    }

    dnGotoxy(3, DIALOG_Y + 2);
    wcout << L"\"" << firstLine;

    if (!secondLine.empty()) {
        dnGotoxy(3, DIALOG_Y + 3);
        wcout << secondLine << L"\"";
    }
    else {
        wcout << L"\"";
    }

    dnHline(1, DIALOG_Y + 5, MAIN_W - 2, L'├', L'─', L'┤');

    for (int i = 0; i < (int)npc.choices.size(); i++) {
        dnGotoxy(4, DIALOG_Y + 6 + i * 2);
        wcout << (i == choiceCursor ? L"▶  " : L"   ");
        wcout << npc.choices[i].question;
    }

    dnGotoxy(4, TOTAL_H - 2);
    wcout << L"↑↓/W/S: 선택 이동   Enter: 질문하기   ESC: 나가기";
}

inline void dnDrawSidebar(const Player& p, const DialogueNPCData& npc) {
    const int SIDE_X = 80;
    const int W = 39;
    const int TOTAL_H = 40;
    const int MAX_HINTS = 17;

    auto line = [&](int y, wchar_t l, wchar_t m, wchar_t r) {
        dnGotoxy(SIDE_X, y);
        wcout << l;
        for (int i = 0; i < W - 2; i++) wcout << m;
        wcout << r;
    };

    auto row = [&](int y) {
        dnGotoxy(SIDE_X, y);
        wcout << L"║";
        for (int i = 0; i < W - 2; i++) wcout << L" ";
        wcout << L"║";
    };

    line(0, L'╔', L'═', L'╗');
    row(1); dnGotoxy(SIDE_X + 2, 1); wcout << L"[ 탐정 정보 ]";
    line(2, L'╠', L'═', L'╣');

    row(3); dnGotoxy(SIDE_X + 2, 3); wcout << L"이름 : " << dnToWide(p.name);
    row(4); dnGotoxy(SIDE_X + 2, 4); wcout << L"위치 : " << npc.location;

    line(9, L'╔', L'═', L'╗');
    row(10);
    dnGotoxy(SIDE_X + 2, 10);
    wcout << L"[ 단서 목록 ] " << p.hints.size() << L"/" << MAX_HINTS;

    line(11, L'╠', L'═', L'╣');

    for (int i = 0; i < MAX_HINTS; i++) {
        row(12 + i);
        dnGotoxy(SIDE_X + 2, 12 + i);

        if (i < (int)p.hints.size()) {
            wcout << L"· " << dnShortHint(p.hints[i]);
        }
        else {
            wcout << L"· (미발견)";
        }
    }

    for (int y = 12 + MAX_HINTS; y < TOTAL_H - 1; y++) row(y);
    line(TOTAL_H - 1, L'╚', L'═', L'╝');
}

inline void runDialogueNPC(DialogueNPCData& npc, Player& p) {
    _setmode(_fileno(stdout), _O_U16TEXT);
    dnWaitReleasedInputKeys();

    int choiceCursor = 0;
    wstring currentDialog = L"...무슨 일이지?";

    while (true) {
        system("cls");

        dnDrawScene(npc);
        dnDrawDialog(npc, currentDialog, choiceCursor);
        dnDrawSidebar(p, npc);

        DialogueInput input = dnGetInput();

        if (input == DN_UP && choiceCursor > 0) {
            choiceCursor--;
        }
        else if (input == DN_DOWN && choiceCursor < (int)npc.choices.size() - 1) {
            choiceCursor++;
        }
        else if (input == DN_ENTER) {
            currentDialog = npc.choices[choiceCursor].answer;
        }
        else if (input == DN_ESC) {
            if (!npc.cleared) {
                addProgress(p);
                npc.cleared = true;
            }
            break;
        }
    }

    _setmode(_fileno(stdout), _O_TEXT);
    system("cls");
}