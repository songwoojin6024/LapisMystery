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
void addProgress(Player& p);

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
        addProgress(p);
        cout << "\n\t[단서가 추가되었습니다.] " << hint << "\n";
    }
    else {
        cout << "\n\t[이미 확인한 단서입니다.]\n";
    }

    cout << "\n\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

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

    cout << "\n\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

    while (_kbhit()) _getch();
    _getch();

    system("cls");
}
inline void showScratchedFloor(Player& p) {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    cout << "\n\n";
    cout << "\t[ 청금석 바닥의 긁힌 자국과 발자국]\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "\t* 무거운 물체를 끌고 이동한 흔적.\n";
    cout << "\t* 발자국이 남아 있는 것으로 보아 사람이 이동한 흔적.\n";

    string hint = "바닥의 긁힌 자국과 발자국";

    if (!hasHint(p, hint)) {
        p.hints.push_back(hint);
        addProgress(p);
        cout << "\n\t[단서가 추가되었습니다.] " << hint << "\n";
    }
    else {
        cout << "\n\t[이미 확인한 단서입니다.]\n";
    }

    cout << "\n\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

    while (_kbhit()) _getch();
    _getch();

    system("cls");
}

inline void showSearchanalysis(Player& p) {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    cout << "\n\n";
    cout << "\t[ 삭제된 연구 메일 ]\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "\t* 초전도체 샘플 확보 필요'라는 제목의 메일이 복구되었다.\n";
    cout << "\t* 수신자는 제갈현철 교수였다.\n";
    cout << "\t* 발신 시각은 청금석 도난 하루 전이다.\n";

    string hint = "청금석 내부 초전도체 성분 분석";

    if (!hasHint(p, hint)) {
        p.hints.push_back(hint);
        addProgress(p);
        cout << "\n\t[단서가 추가되었습니다.] " << hint << "\n";
    }
    else {
        cout << "\n\t[이미 확인한 단서입니다.]\n";
    }

    cout << "\n\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

    while (_kbhit()) _getch();
    _getch();

    system("cls");
}
inline void showBloodyGlove(Player& p) {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    cout << "\n\n";
    cout << "\t[ 자판기 밑 수색 ]\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "\t자판기 아래쪽을 살펴보았다.\n";
    cout << "\t먼지와 동전 사이에 무언가 구겨진 천이 보인다.\n\n";

    cout << "\t* 피 묻은 면장갑을 발견했다.\n";
    cout << "\t* 장갑 안쪽에는 유리 조각이 조금 박혀 있다.\n";
    cout << "\t* 누군가 깨진 창문 근처에서 손을 다친 듯하다.\n";
    cout << "\t* 장갑 안쪽 이름표에는 '박보승'이라고 적혀 있다.\n";

    string hint = "박보승의 피 묻은 장갑";

    if (!hasHint(p, hint)) {
        p.hints.push_back(hint);
        addProgress(p);
        cout << "\n\t[단서가 추가되었습니다.] " << hint << "\n";
    }
    else {
        cout << "\n\t[이미 확인한 단서입니다.]\n";
    }

    cout << "\n\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

    while (_kbhit()) _getch();
    _getch();

    system("cls");
}
inline void showpcsearch(Player& p) {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    cout << "\n\n";
    cout << "\t[ 송우진 PC 로그인 기록 ]\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "\t새벽 2시 10분, 송우진 계정으로 과제 파일이 저장되어 있다..\n";

    string hint = "pc 로그인 기록";

    if (!hasHint(p, hint)) {
        p.hints.push_back(hint);
        addProgress(p);
        cout << "\n\t[단서가 추가되었습니다.] " << hint << "\n";
    }
    else {
        cout << "\n\t[이미 확인한 단서입니다.]\n";
    }

    cout << "\n\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

    while (_kbhit()) _getch();
    _getch();

    system("cls");
}
inline void showElectricLine(Player& p) {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    cout << "\n\n";
    cout << "\t[ 경비실 전원 차단 흔적 ]\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "\tCCTV 전원선이 강제로 뽑긴 흔적이 있다..\n";
    cout << "\t전원함 근처에서 교수 연구실 출입증 끈 조각이 발견되었다..\n";
    cout << "\tCCTV 공백은 우발적인 고장이 아닌 의도적인 차단으로 보인다...\n";

    string hint = "경비실 전원 차단 흔적";

    if (!hasHint(p, hint)) {
        p.hints.push_back(hint);
        addProgress(p);
        cout << "\n\t[단서가 추가되었습니다.] " << hint << "\n";
    }
    else {
        cout << "\n\t[이미 확인한 단서입니다.]\n";
    }

    cout << "\n\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

    while (_kbhit()) _getch();
    _getch();

    system("cls");
}
inline void showMasterKey(Player& p) {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    cout << "\n\n";
    cout << "\t[ 교수 마스터키 사용 기록 ]\n\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "\t교수 마스터키 사용 기록이 남아 있다..\n";
    cout << "\t사용된 카드는 제갈현철 교수의 마스터키였다..\n";
    cout << "\t기록 일부가 삭제되었지만 복구 흔적이 남아 있다...\n";

    string hint = "마스터키 사용 기록";

    if (!hasHint(p, hint)) {
        p.hints.push_back(hint);
        addProgress(p);
        cout << "\n\t[단서가 추가되었습니다.] " << hint << "\n";
    }
    else {
        cout << "\n\t[이미 확인한 단서입니다.]\n";
    }

    cout << "\n\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

    while (_kbhit()) _getch();
    _getch();

    system("cls");
}