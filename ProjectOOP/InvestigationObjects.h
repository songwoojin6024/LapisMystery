#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "GameManager.h"

using namespace std;
//중복 방지
inline bool hasHint(Player& p, const string& hint) {
    for (const string& h : p.hints) {
        if (h == hint) {
            return true;
        }
    }
    return false;
}
//단서와 단서창 등록
inline void showSearchRecord(Player& p) {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    cout << "\n\n";
    cout << "\t[ 누군가의 검색 기록 ]\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "\t* \"청금석 시세\"\n";
    cout << "\t* \"대형 조형물 판매\"\n";
    cout << "\t* \"중고 운반 장비\"\n";

    string hint = "수상한 검색기록";

    if (!hasHint(p, hint)) {
        p.hints.push_back(hint);
        cout << "\n\t[단서가 추가되었습니다.] " << hint << "\n";
    }
    else {
        cout << "\n\t[이미 확인한 단서입니다.]\n";
    }

    cout << "\n\n\t(아무 키나 누르면 돌아갑니다.)";

    while (_kbhit()) _getch();
    _getch();

    system("cls");
}

inline void showEmptyObject() {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

    cout << "\n\n";
    cout << "\t확인해 보았다.\n";
    cout << "\t하지만 특별한 것은 없어 보인다.\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "\n\n\t(아무 키나 누르면 돌아갑니다.)";

    while (_kbhit()) _getch();
    _getch();

    system("cls");
}
inline void showScratchedFloor(Player& p) {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    cout << "\n\n";
    cout << "\t[ 청금석 바닥의 긁힌 자국 ]\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "\t* 무거운 물체를 끌고 이동한 흔적.\n";

    string hint = "바닥의 긁힌 자국";

    if (!hasHint(p, hint)) {
        p.hints.push_back(hint);
        cout << "\n\t[단서가 추가되었습니다.] " << hint << "\n";
    }
    else {
        cout << "\n\t[이미 확인한 단서입니다.]\n";
    }

    cout << "\n\n\t(아무 키나 누르면 돌아갑니다.)";

    while (_kbhit()) _getch();
    _getch();

    system("cls");
}
inline void showSearchanalysis(Player& p) {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    cout << "\n\n";
    cout << "\t[ 청금석 내부 초전도체 성분 분석표 ]\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "\t* 청금석 내부 초전도체 성분 분석 결과.\n";

    string hint = "청금석 내부 초전도체 성분 분석";

    if (!hasHint(p, hint)) {
        p.hints.push_back(hint);
        cout << "\n\t[단서가 추가되었습니다.] " << hint << "\n";
    }
    else {
        cout << "\n\t[이미 확인한 단서입니다.]\n";
    }

    cout << "\n\n\t(아무 키나 누르면 돌아갑니다.)";

    while (_kbhit()) _getch();
    _getch();

    system("cls");
}