#include"Common.h"
using namespace std;

void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void renderGame(Player& p, MapData& m) {
    gotoxy(0, 0);
    for (int i = 0; i < 40; i++) {
        printf("%s\n", m.mapArray[i]);
    }
    gotoxy(p.x, p.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m.playerColor);
    switch (p.dir) {
    case UP:    cout << "¡ã"; break;
    case DOWN:  cout << "¡å"; break;
    case LEFT:  cout << "¢¸"; break;
    case RIGHT: cout << "¢º"; break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    gotoxy(0, 41);
    cout << "==========================================================" << endl;
    cout << " [STATUS] ";
    for (int i = 0; i < p.hearts; i++) cout << "¢¾ ";
    for (int i = p.hearts; i < 3; i++) cout << "¢½ ";
    int percent = 0;

    if (p.maxProgress > 0) {
        percent = (p.progress * 100) / p.maxProgress;
    }

    cout << "| Money: " << p.money << "¿ø | Hints: " << p.hints.size()
        << " | Progress: " << percent << "%" << endl;
    cout << " [POS] X: " << p.x << " Y: " << p.y << endl;
    cout << "==========================================================" << endl;
}

void initConsole() {
    system("mode con cols=120 lines=47");
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