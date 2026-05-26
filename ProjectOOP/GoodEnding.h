#pragma once
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

const int GE_TEXT_SPEED = 100;
const int GE_DIALOGUE_WAIT = 3000;
const int GE_NEWS_Y = 0;
const int GE_FACE_Y = 9;
const int GE_FACE_HEIGHT = 18;
const int GE_DIALOGUE_Y = GE_FACE_Y + GE_FACE_HEIGHT + 2;

inline void geGotoxy(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

inline void geHideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

inline void geFace1()
{
    cout << "                _############＼                " << endl;
    cout << "             /#################＼              " << endl;
    cout << "            /##'         #######＼             " << endl;
    cout << "           /##             ######＼            " << endl;
    cout << "           ###               #####             " << endl;
    cout << "           ###  =====    ===== ##|             " << endl;
    cout << "            ##    /■＼    /■＼  /            " << endl;
    cout << "            ＼|                |/)             " << endl;
    cout << "             0|      \\__/      |             " << endl;
    cout << "             ㄴ|    ______    /                " << endl;
    cout << "               ＼  ＼_____/  /                 " << endl;
    cout << "                ＼__________/                  " << endl;
    cout << "           _____|           |____              " << endl;
    cout << "       ___／    ＼          /    ＼___         " << endl;
    cout << "                 ＼__    __/                   " << endl;
    cout << "       [박기자]   |  ＼ /  |                   " << endl;
    cout << "                                               " << endl;
}

inline void geFace2()
{
    cout << "                _############＼                " << endl;
    cout << "             /#################＼              " << endl;
    cout << "            /##'         #######＼             " << endl;
    cout << "           /##             ######＼            " << endl;
    cout << "           ###               #####             " << endl;
    cout << "           ###  =====    ===== ##|             " << endl;
    cout << "            ##    /■＼    /■＼  /            " << endl;
    cout << "            ＼|                |/)             " << endl;
    cout << "             0|      \\__/      |             " << endl;
    cout << "             ㄴ|    ______    /                " << endl;
    cout << "               ＼     --     /                 " << endl;
    cout << "                ＼__________/                  " << endl;
    cout << "           _____|           |____              " << endl;
    cout << "       ___／    ＼          /    ＼___         " << endl;
    cout << "                 ＼__    __/                   " << endl;
    cout << "       [박기자]   |  ＼ /  |                   " << endl;
    cout << "                                               " << endl;
}

inline void geDrawReporterFace(int frame)
{
    geGotoxy(0, GE_FACE_Y);

    if (frame == -1) geFace2();
    else if (frame % 2 == 0) geFace1();
    else geFace2();
}

inline void geNoFace(int frame)
{
    // 마지막 Good End 화면은 얼굴 출력 없음
}

inline void geTypeDialogue(const string& text, int& frame, void (*drawFace)(int))
{
    geGotoxy(0, GE_DIALOGUE_Y);
    cout << string(110, ' ');

    string currentText;

    for (size_t i = 0; i < text.size();)
    {
        drawFace(frame);
        frame++;

        unsigned char c = text[i];
        int charSize = 1;

        if ((c & 0xF0) == 0xE0) charSize = 3;
        else if ((c & 0xE0) == 0xC0) charSize = 2;
        else if ((c & 0xF8) == 0xF0) charSize = 4;

        currentText += text.substr(i, charSize);

        geGotoxy(0, GE_DIALOGUE_Y);
        cout << currentText;

        i += charSize;
        Sleep(GE_TEXT_SPEED);
    }

    drawFace(-1);
}

inline void gePrintNewsTitle1()
{
    geGotoxy(0, GE_NEWS_Y);
    cout << "______  _____  _____   _   _  _____  _    _  _____   _ " << endl;
    cout << "| ___ \\|_   _||  __ \\ | \\ | ||  ___|| |  | |/  ___| | |" << endl;
    cout << "| |_/ /  | |  | |  \\/ |  \\| || |__  | |  | |\\ `--.  | |" << endl;
    cout << "| ___ \\  | |  | | __  | . ` ||  __| | |/\\| | `--. \\ | |" << endl;
    cout << "| |_/ / _| |_ | |_\\ \\ | |\\  || |___ \\  /\\  //\\__/ / |_|" << endl;
    cout << "\\____/  \\___/  \\____/ \\_| \\_/\\____/  \\/  \\/ \\____/  (_)" << endl;
    cout << "                                                         " << endl;
    cout << "                                                         " << endl;
    cout << "                                                         " << endl;
}

inline void gePrintNewsTitle2()
{
    geGotoxy(0, GE_NEWS_Y);
    cout << " GEDENEWS                                         ____ " << endl;
    cout << "                (만세!)      (우와아아!)         /    \\ " << endl;
    cout << "               \\O/         \\O/                  /  청  \\" << endl;
    cout << "                |           |                   |  금  |" << endl;
    cout << "               /＼         /＼                  |  석  |" << endl;
    cout << "                                                \\______/" << endl;
    cout << "   ====================================================  " << endl;
    cout << "     돌아온 청금석 계대의 평화 지켜지다!   " << endl;
    cout << "   ====================================================  " << endl;
}

inline void gePrintNewsTitle3()
{
    geGotoxy(0, GE_NEWS_Y);
    cout << " GEDENEWS                                                " << endl;
    cout << "                     _____      _____       _____        " << endl;
    cout << "                   _|__*__|_   /-----＼   _|__*__|_      " << endl;
    cout << "                    |     |    |ㅠ ㅠ|     |     |       " << endl;
    cout << "                   _＼___/_   / ===== ＼  _＼___/_       " << endl;
    cout << "                  |        |  (O)---(O)  |        |      " << endl;
    cout << "   ====================================================  " << endl;
    cout << "     붙잡힌 제갈현철 교수, 감옥으로 이송중              " << endl;
    cout << "   ====================================================  " << endl;
}

inline void gePrintNewsTitle4()
{
    geGotoxy(0, GE_NEWS_Y);
    cout << "                                        ____               " << endl;
    cout << " GEDENEWS              ____  ____      //  ＼＼              " << endl;
    cout << "                      |   ＼/    |     ||  //             " << endl;
    cout << "                  ____|          |___     //              " << endl;
    cout << "                 |    |__________|   |    ||              " << endl;
    cout << "                 ＼__________________/    ()              " << endl;
    cout << "   ====================================================  " << endl;
    cout << "     홀연히 사라진 탐정! 대구의 다크나이트?              " << endl;
    cout << "   ====================================================  " << endl;
}

inline void gePrintEndingTitle()
{
    geGotoxy(0, GE_NEWS_Y);
    cout << " _____                    _   _____             _ " << endl;
    cout << "|  __ \\                  | | |  ___|           | |" << endl;
    cout << "| |  \\/  ___    ___    __| | | |__   _ __    __| |" << endl;
    cout << "| | __  / _ \\  / _ \\  / _` | |  __| | '_ \\  / _` |" << endl;
    cout << "| |_\\ \\| (_) || (_) || (_| | | |___ | | | || (_| |" << endl;
    cout << " \\____/ \\___/  \\___/  \\__,_| \\____/ |_| |_| \\__,_|" << endl;
    cout << "                                                  " << endl;
}

inline void gePlayNewsScene(void (*printTitle)(), const string dialogues[], int count)
{
    system("cls");
    geHideCursor();
    printTitle();

    int frame = 0;
    for (int i = 0; i < count; i++)
    {
        geTypeDialogue(dialogues[i], frame, geDrawReporterFace);
        Sleep(GE_DIALOGUE_WAIT);
    }
}

inline void gePlayEndScene()
{
    system("cls");
    geHideCursor();
    gePrintEndingTitle();

    string dialogues[] = {
        "       모든 사건이 무사히 해결되었다.",
        "       청금석은 제자리를 찾았고, 학교에는 다시 평화가 찾아왔다.",
        "       플레이해주셔서 감사합니다!"
    };

    int frame = 0;
    for (int i = 0; i < 3; i++)
    {
        geTypeDialogue(dialogues[i], frame, geNoFace);
        Sleep(GE_DIALOGUE_WAIT);
    }
}

inline void playGoodEnding()
{
    system("mode con cols=120 lines=45");
    system("cls");
    geHideCursor();

    string scene1[] = {
        "특종입니다! 마침내 청금석 도난 사건의 전말이 밝혀졌습니다."
    };

    string scene2[] = {
        "보시는 것과 같이 청금석이 되돌아왔습니다."
    };

    string scene3[] = {
        "범인은 제갈현철 교수, 현재 보시는 바와 같이 감옥으로 이송중입니다.",
        "경찰은 적극적인 조사를 이어나갈 것으로 보입니다."
    };

    string scene4[] = {
        "현재, 범인을 잡는데 지대한 공을 세운 탐정이 돌연 사라졌다고 합니다.",
        "소문에 따르면 대통령 표창장마저 거절했다는데요. 어디로 가셨을까요?"
    };

    gePlayNewsScene(gePrintNewsTitle1, scene1, 1);
    gePlayNewsScene(gePrintNewsTitle2, scene2, 1);
    gePlayNewsScene(gePrintNewsTitle3, scene3, 2);
    gePlayNewsScene(gePrintNewsTitle4, scene4, 2);
    gePlayEndScene();

    system("cls");
}