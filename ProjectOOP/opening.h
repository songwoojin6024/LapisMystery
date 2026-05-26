#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "GameManager.h"
using namespace std;


inline void openingGotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
inline void showOpeningSkipGuide() {
    openingGotoxy(70, 38);
    cout << "[ESC: 오프닝 스킵 ]";

    openingGotoxy(0, 8); // 다음 오프닝 텍스트가 시작될 위치
}

inline bool isOpeningSkipPressed() {
    return (GetAsyncKeyState(VK_ESCAPE) & 0x8000);
}

inline bool openingSleep(int ms) {
    int elapsed = 0;

    while (elapsed < ms) {
        if (isOpeningSkipPressed()) {
            return true;
        }

        Sleep(50);
        elapsed += 50;
    }

    return false;
}

// ── 타이핑 효과 ─────────────────────────────────────────
inline bool printDialogue(const string& text, int delay = 50) {
    for (size_t i = 0; i < text.length(); i++) {
        if (isOpeningSkipPressed()) {
            return true;
        }

        if (text[i] & 0x80) {
            cout << text[i] << text[i + 1];
            i++;
        }
        else {
            cout << text[i];
        }

        if (openingSleep(delay)) {
            return true;
        }
    }

    cout << endl;
    return false;
}

// ── Scene1 아트 ─────────────────────────────────────────
inline void art1() {
    cout << " _____  _____  _____   ____         __   __        __   __" << endl;
    cout << "/ __  \\|  _  |/ __  \\ / ___|        \\ \\ / /        \\ \\ / /" << endl;
    cout << "`' / /'| |/' |`' / /'/ /___  ______  \\ V /  ______  \\ V / " << endl;
    cout << "  / /  |  /| |  / /  | ___ \\|______| /   \\ |______| /   \\ " << endl;
    cout << "./ /___\\ |_/ /./ /___| \\_/ |        / /^\\ \\        / /^\\ \\" << endl;
    cout << "\\_____/ \\___/ \\_____/\\_____/        \\/   \\/        \\/   \\/" << endl;
}

// ── Scene2 아트들 ────────────────────────────────────────
inline void art2() { cout << "                      ____ \n                     /    \\ \n                    /  청  \\\n                    |  금  |\n                    |  석  |\n                    \\______/" << endl; }
inline void art2_2() { cout << "                      l___ \n                     /    \\ \n                    /  청  \\\n                    |  금  |\n                    |  석  |\n                    \\______/" << endl; }
inline void art2_3() { cout << "                      l___ \n                     /l   \\ \n                    /  청  \\\n                    |  금  |\n                    |  석  |\n                    \\______/" << endl; }
inline void art2_4() { cout << "                      l___ \n                     /l   \\ \n                    / l청  \\\n                    |  금  |\n                    |  석  |\n                    \\______/" << endl; }
inline void art2_5() { cout << "                      l___ \n                     /l   \\ \n                    / l청  \\\n                    | l금  |\n                    |  석  |\n                    \\______/" << endl; }
inline void art2_6() { cout << "                      l___ \n                     /l   \\ \n                    / l청  \\\n                    |_l금_ |\n                    |  석  |\n                    \\______/" << endl; }
inline void art2_7() { cout << "                      l___ \n                     /l   \\ \n                    / l청  \\\n                    |_l금__|\n                    |  석  |\n                    \\______/" << endl; }
inline void art2_8() { cout << "                     /l   \\ \n                    / l청  \\\n                    |_l금__|\n                    |  석  |\n                    \\______/\n                           " << endl; }
inline void art2_9() { cout << "                    / l청  \\\n                    |_l금__|\n                    |  석  |\n                    \\______/\n                           \n                           " << endl; }
inline void art2_10() { cout << "                    |_l금__|\n                    |  석  |\n                    \\______/\n                           \n                           \n                           " << endl; }
inline void art2_11() { cout << "                    |  석  |\n                    \\______/\n                           \n                           \n                           \n                           " << endl; }
inline void art2_12() { cout << "                    \\______/\n                           \n                           \n                           \n                           \n                           " << endl; }
inline void art2_13() { cout << "                           \n                           \n                           \n                           \n                           \n                           " << endl; }

// ── Scene3 아트들 ────────────────────────────────────────
inline void art3() {
    cout << "      ############        ##########    ####      ##########    ####      ####" << endl;
    cout << "    ################     #############  ####     ############   ####      ####" << endl;
    cout << "    ####        ####     ###      ####  ####    ####      ####  ########  ####" << endl;
    cout << "    ##            ##    ####      ####  ####    ####      ####  ####      ####" << endl;
    cout << "    ####        ####    ####      ####  ########  ############  ####      ####" << endl;
    cout << "    ################     ###      ####  ####      ##########    ####      ####" << endl;
    cout << "      ############        ############  ####                              ####" << endl;
    cout << "                           ##########   ####        ################      ####" << endl;
    cout << "                                        ####                    ####          " << endl;
    cout << "########################                ####                    ####      ####" << endl;
    cout << "                                        ####                    ####      ####" << endl;
    cout << "                                                                ####          " << endl;
}
inline void art4() {
    cout << "                                           " << endl;
    cout << "                ###############                " << endl;
    cout << "              /########  ##  ###               " << endl;
    cout << "             /# ┘└              #＼          " << endl;
    cout << "            /#  ┓┏              ##＼                " << endl;
    cout << "            ##  ==           ==  ###            " << endl;
    cout << "           ###    ===     ===   ##|               " << endl;
    cout << "            ##ㅡ[  ■ ]ㅡ[ ■ ]ㅡ/                      " << endl;
    cout << "            ＼|                |/)                   " << endl;
    cout << "              |   /  \\__/ ＼   |                         " << endl;
    cout << "               |  { ______ }  /                      " << endl;
    cout << "               ＼     --     /                       " << endl;
    cout << "                | ＼______↗ |                               " << endl;
    cout << "           _____|           |____                 " << endl;
    cout << "       ___／    ＼          /    ＼___            " << endl;
    cout << "                 ＼__    __/                     " << endl;
    cout << "       [      ]   |  ＼ /  |                        " << endl;
}
inline void art5() {
    cout << "         #                                 " << endl;
    cout << "         #      ###############                " << endl;
    cout << "         #    /########  ##  ###               " << endl;
    cout << "         #   /#                #＼          " << endl;
    cout << "         #  /#                 ##＼                " << endl;
    cout << "         . ##   ===       ===   ###            " << endl;
    cout << "           ##  ==            == ###            " << endl;
    cout << "            ##ㅡ[  ■ ]ㅡ[ ■ ]ㅡ/                      " << endl;
    cout << "            ＼|                |/)                   " << endl;
    cout << "              |   /  \\__/ ＼   |                         " << endl;
    cout << "               |  { ______ }  /                      " << endl;
    cout << "               ＼     --     /                       " << endl;
    cout << "                | ＼______↗ |                               " << endl;
    cout << "           _____|           |____                 " << endl;
    cout << "       ___／    ＼          /    ＼___            " << endl;
    cout << "                 ＼__    __/                     " << endl;
    cout << "       [      ]   |  ＼ /  |                        " << endl;
}
inline void art6() {
    cout << "                ###############                    " << endl;
    cout << "              /########  ##  ###                   " << endl;
    cout << "             /#                #＼                " << endl;
    cout << "            /#                 ##＼               " << endl;
    cout << "            ##                  ###               " << endl;
    cout << "           ###  =====     ===== ##|   _____        " << endl;
    cout << "            ##ㅡ[  ■ ]ㅡ[ ■ ]ㅡ/   |     |       " << endl;
    cout << "            ＼|                |/)   | 112 |       " << endl;
    cout << "              |   /  \\__/ ＼   |     |     |       " << endl;
    cout << "               |  { ______ }  /       -----        " << endl;
    cout << "               ＼     --     /                     " << endl;
    cout << "                | ＼______↗ |                     " << endl;
    cout << "           _____|           |____                  " << endl;
    cout << "       ___／    ＼          /    ＼___             " << endl;
    cout << "                 ＼__    __/                       " << endl;
    cout << "       [      ]   |  ＼ /  |                       " << endl;
}
inline void art7() {
    cout << "        #       ###############                    " << endl;
    cout << "        #     /########  ##  ###                   " << endl;
    cout << "        #    /#                #＼                " << endl;
    cout << "        #   /#                 ##＼               " << endl;
    cout << "        .   ##                  ###               " << endl;
    cout << "           ###  =====     ===== ##|   _____        " << endl;
    cout << "            ##ㅡ[  ■ ]ㅡ[ ■ ]ㅡ/   |     |       " << endl;
    cout << "            ＼|                |/)   | 112 |       " << endl;
    cout << "              |   /  \\__/ ＼   |     |     |       " << endl;
    cout << "               |  { ______ }  /       -----        " << endl;
    cout << "               ＼     --     /                     " << endl;
    cout << "                | ＼______↗ |                     " << endl;
    cout << "           _____|           |____                  " << endl;
    cout << "       ___／    ＼          /    ＼___             " << endl;
    cout << "                 ＼__    __/                       " << endl;
    cout << "       [      ]   |  ＼ /  |                       " << endl;
}
inline void art8() {
    cout << "################################################################" << endl;
    cout << "#                                                              #" << endl;
    cout << "#          # #   ####    #       #                             #" << endl;
    cout << "#   #####  # #  ##  ##   #       #       #########   ######### #" << endl;
    cout << "#       #  # #  #    #   #       #         #   #     ##        #" << endl;
    cout << "#      ##  # #  #    #   #      ###        #   #     ########  #" << endl;
    cout << "#      ##### #  ##  ##   #    ### ###      #   #     ##        #" << endl;
    cout << "#      ##### #   ####    #   ###   ###     #   #     ##        #" << endl;
    cout << "#     ##   # #           #  ##   #   ##  #########   ######### #" << endl;
    cout << "#   ###    # #    ########       #                             #" << endl;
    cout << "#  ##      # #    #      #       #                             #" << endl;
    cout << "#  #       # #    #      # #####################################" << endl;
    cout << "#          # #    #      #                                     #" << endl;
    cout << "#          # #    ########                                     #" << endl;
    cout << "#                                                              #" << endl;
    cout << "################################################################" << endl;
}

// ── 오프닝 전체 실행 ─────────────────────────────────────
inline void playOpening() {
    // Scene 1
    system("cls"); art1(); cout << "\n\n";
    showOpeningSkipGuide();
    openingGotoxy(0, 8);
    if (openingSleep(1000)) return;
    if (printDialogue("2026년 어느 여름날...", 200)) return;
    if (openingSleep(3000)) return;

    system("cls"); art1(); cout << "\n\n";
    if (printDialogue("계명대의 역사에 한 획을 그을 전설적인 사건이 일어난다...", 100)) return;
    if (openingSleep(3000)) return;

    // Scene 2
    system("cls"); art2(); cout << "\n\n";
    showOpeningSkipGuide();
    openingGotoxy(0, 8);
    if (printDialogue("계명의 국보 청금석.", 150)) return;
    if (openingSleep(3000)) return;

    system("cls"); art2(); cout << "\n\n";
    if (printDialogue("총장님께서는 학생 만큼 귀중히 여기신다.", 150)) return;
    if (openingSleep(3000)) return;

    system("cls"); art2(); cout << "\n\n";
    if (printDialogue("이 영석(靈石)의 값은 감히 헤아릴 수 조차 없었고.....", 150)) return;
    if (openingSleep(3000)) return;

    system("cls"); art2(); cout << "\n\n";
    if (printDialogue("감히 그 누구도 넘보지 못할 것이 분명했다.", 150)) return;
    if (openingSleep(2000)) return;

    // 도난 애니메이션
    void(*anims[])() = { art2_2, art2_3, art2_4, art2_5, art2_6, art2_7, art2_8, art2_9, art2_10, art2_11, art2_12, art2_13 };
    for (auto& f : anims) {
        system("cls");
        f();
        cout << "\n\n";
        if (openingSleep(1000)) return;
    }

    system("cls"); art2_13(); cout << "\n\n";
    if (printDialogue("도둑이다!!!!!!!!!!!", 50)) return;
    if (openingSleep(3000)) return;

    // Scene 3
    system("cls"); cout << "\n\n";
    showOpeningSkipGuide();
    openingGotoxy(0, 8);
    if (printDialogue("다음날 총장실...", 150)) return;
    if (openingSleep(2000)) return;

    system("cls"); art3(); cout << "\n\n";
    if (openingSleep(3000)) return;

    system("cls"); art4(); cout << "\n\n";
    if (printDialogue("청금석이 도난 당했다고요?", 200)) return;
    if (openingSleep(1000)) return;

    system("cls"); art4(); cout << "\n\n";
    if (printDialogue("세상에 이런 일이!", 200)) return;
    if (openingSleep(1000)) return;

    system("cls"); art5(); cout << "\n\n";
    if (printDialogue("따르르릉! 따르르릉!", 200)) return;
    if (openingSleep(1000)) return;

    system("cls"); art5(); cout << "\n\n";
    if (printDialogue("그 순간 총장실의 전화가 울린다.", 200)) return;
    if (openingSleep(1000)) return;

    system("cls"); art6(); cout << "\n\n";
    if (printDialogue("경찰입니까? 혹시 범인이 잡혔소?", 150)) return;
    if (openingSleep(1000)) return;

    system("cls"); art7(); cout << "\n\n";
    if (printDialogue("무슨? 그런 증거를 찾았다고요?", 150)) return;
    if (openingSleep(1000)) return;

    system("cls"); cout << "\n\n";
    if (printDialogue("증거는 충격적이었다...", 150)) return;
    if (openingSleep(1000)) return;

    system("cls"); cout << "\n\n";
    if (printDialogue("사건이 발생한 곳에서 발견된 것은...", 200)) return;
    if (openingSleep(3000)) return;

    system("cls"); art8(); cout << "\n\n";
    if (printDialogue("게임 소프트웨어학과 마크!!!!", 100)) return;
    if (openingSleep(2000)) return;

    system("cls"); art4(); cout << "\n\n";
    if (printDialogue("오호라, 그렇다면 범인은 그 학과 학생중 하나였다?", 150)) return;
    if (openingSleep(1000)) return;

    system("cls"); art4(); cout << "\n\n";
    if (printDialogue("그 학과 학과장에게 알려라! 만약 범인을 못찾으면 게임소프트웨어 학과의 예산으로 청금석을 사겠다!", 150)) return;
    if (openingSleep(1000)) return;

    system("cls"); cout << "\n\n";
    if (printDialogue("청금석의 값어치는 천문학적이다, 때문에 범인을 못찾으면 학과가 사라진다!", 150)) return;
    if (openingSleep(2000)) return;

    system("cls"); cout << "\n\n";
    if (printDialogue("학과장께서는 명석하다고 소문난 탐정에게 의뢰를 넣으셨고 그 사람이 바로...", 150)) return;
    if (openingSleep(2000)) return;

    system("cls"); cout << "\n\n";
    if (printDialogue("당! 신! ", 300)) return;
    if (openingSleep(3000)) return;

    system("cls"); cout << "\n\n";
    if (printDialogue("범인을 찾아라! 청금석을 찾아라! 당신의 두뇌에 대구 최고 학과의 운명이 달렸다!", 150)) return;
    if (openingSleep(2500)) return;
}