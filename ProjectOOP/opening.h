#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "GameManager.h"
using namespace std;

// ── 타이핑 효과 ─────────────────────────────────────────
inline void printDialogue(const string& text, int delay = 50) {
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] & 0x80) { cout << text[i] << text[i + 1]; i++; }
        else cout << text[i];
        Sleep(delay);
    }
    cout << endl;
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
    Sleep(1000);
    printDialogue("2026년 어느 여름날...", 200);
    Sleep(3000);
    system("cls"); art1(); cout << "\n\n";
    printDialogue("계명대의 역사에 한 획을 그을 전설적인 사건이 일어난다...", 100);
    Sleep(3000);

    // Scene 2
    system("cls"); art2(); cout << "\n\n";
    printDialogue("계명의 국보 청금석.", 150);
    Sleep(3000);
    system("cls"); art2(); cout << "\n\n";
    printDialogue("총장께서는 이 돌을 학생 보ㄷ... 아니 학생 만큼 귀중히 여기신다.", 150);
    Sleep(3000);
    system("cls"); art2(); cout << "\n\n";
    printDialogue("이 영석(靈石)의 값은 감히 헤아릴 수 조차 없었다.", 150);
    Sleep(3000);
    system("cls"); art2(); cout << "\n\n";
    printDialogue("때문에 총장께서는 학생들의 등록금을 아주 '조금' 올려 그 돈으로 천라지망(天羅地網)을 펼치니...", 150);
    Sleep(3000);
    system("cls"); art2(); cout << "\n\n";
    printDialogue("감히 그 누구도 넘보지 못할 것이 분명했다.", 150);
    Sleep(2000);

    // 도난 애니메이션
    void(*anims[])() = { art2_2, art2_3, art2_4, art2_5, art2_6, art2_7, art2_8, art2_9, art2_10, art2_11, art2_12, art2_13 };
    for (auto& f : anims) { system("cls"); f(); cout << "\n\n"; Sleep(1000); }
    system("cls"); art2_13(); cout << "\n\n";
    printDialogue("도둑이다!!!!!!!!!!!", 50);
    Sleep(3000);

    // Scene 3
    system("cls"); cout << "\n\n";
    printDialogue("다음날 총장실...", 150);
    Sleep(2000);
    system("cls"); art3(); cout << "\n\n"; Sleep(3000);
    system("cls"); art4(); cout << "\n\n";
    printDialogue("청금석이 도난 당했다고요?", 200); Sleep(1000);
    system("cls"); art4(); cout << "\n\n";
    printDialogue("세상에 이런 일이!", 200); Sleep(1000);
    system("cls"); art5(); cout << "\n\n";
    printDialogue("따르르릉! 따르르릉!", 200); Sleep(1000);
    system("cls"); art5(); cout << "\n\n";
    printDialogue("그 순간 총장실의 전화가 울린다.", 200); Sleep(1000);
    system("cls"); art6(); cout << "\n\n";
    printDialogue("경찰입니까? 혹시 범인이 잡혔소?", 150); Sleep(1000);
    system("cls"); art7(); cout << "\n\n";
    printDialogue("무슨? 그런 증거를 찾았다고요?", 150); Sleep(1000);
    system("cls"); cout << "\n\n";
    printDialogue("증거는 충격적이었다...", 150); Sleep(1000);
    system("cls"); cout << "\n\n";
    printDialogue("사건이 발생한 곳에서 발견된 것은...", 200); Sleep(3000);
    system("cls"); art8(); cout << "\n\n";
    printDialogue("게임 소프트웨어학과 마크!!!!", 100); Sleep(2000);
    system("cls"); art4(); cout << "\n\n";
    printDialogue("오호라, 그렇다면 범인은 그 학과 학생중 하나렸다?", 150); Sleep(1000);
    system("cls"); art4(); cout << "\n\n";
    printDialogue("그 학과 학과장에게 알려라! 만약 범인을 못찾으면 게임소프트웨어 학과의 예산으로 청금석을 사겠다!", 150); Sleep(1000);
    system("cls"); cout << "\n\n";
    printDialogue("청금석의 값어치는 천문학적이다, 때문에 범인을 못찾으면 학과가 사라진다!", 150); Sleep(2000);
    system("cls"); cout << "\n\n";
    printDialogue("학과장께서는 명석하다고 소문난 탐정에게 의뢰를 넣으셨고 그 사람이 바로...", 150); Sleep(2000);
    system("cls"); cout << "\n\n";
    printDialogue("당! 신! ", 300); Sleep(3000);
    system("cls"); cout << "\n\n";
    printDialogue("범인을 찾아라! 청금석을 찾아라! 당신의 두뇌에 대구 최고 학과의 운명이 달렸다!", 150); Sleep(2500);
}