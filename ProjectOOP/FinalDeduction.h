#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "GoodEnding.h"
#include "GameManager.h"

using namespace std;

inline char getNumberChoice(char minKey, char maxKey) {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    while (true) {
        for (char key = minKey; key <= maxKey; key++) {
            if (GetAsyncKeyState(key) & 0x8000) {
                while (GetAsyncKeyState(key) & 0x8000) {
                    Sleep(10);
                }
                return key;
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            while (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                Sleep(10);
            }
            return 27;
        }

        Sleep(10);
    }
}

inline bool askDeductionQuestion(
    const string& title,
    const string& question,
    const string& a,
    const string& b,
    const string& c,
    char correct
) {
    system("cls");

    cout << "\n\n\t[ " << title << " ]\n\n";
    cout << "\t" << question << "\n\n";

    cout << "\t1. " << a << "\n";
    cout << "\t2. " << b << "\n";
    cout << "\t3. " << c << "\n";

    cout << "\n\t정답을 선택하세요. ESC: 취소\n";

    char choice = getNumberChoice('1', '3');

    if (choice == 27) {
        return false;
    }

    return choice == correct;
}

inline void showDeductionFail() {
    system("cls");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

    cout << "\n\n\t[ 추리 실패 ]\n\n";
    cout << "\t단서의 연결이 어긋났다.\n";
    cout << "\t아직 사건을 확신하기엔 부족하다.\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

    while (true) {
        if (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
            GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            while (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
                GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                Sleep(10);
            }
            break;
        }

        Sleep(10);
    }

    system("cls");
}

inline void runFinalDeduction(GameState& state, Player& p) {
    system("cls");

    if (p.hints.size() < 8) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\n\n\t아직 결정적인 단서가 부족하다.\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        cout << "\n\t조사를 더 진행한 뒤 다시 오자.";
        cout << "\n\n\t(Enter 또는 ESC를 누르면 돌아갑니다.)";

        while (true) {
            if (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
                GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                while (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
                    GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                    Sleep(10);
                }
                break;
            }

            Sleep(10);
        }

        system("cls");
        return;
    }

    bool q1 = askDeductionQuestion(
        "최종 추리 1",
        "청금석은 단순한 장식품이 아니었다. 범인은 왜 굳이 위험을 감수하고 청금석을 훔쳤을까? ",
        "돈이 급해서 바로 팔려고 했다.",
        "내부 초전도체 성분을 연구에 이용하려 했다.",
        "학과 예산을 빼돌리기 위해서였다.",
        '2'
    );

    if (!q1) {
        showDeductionFail();
        return;
    }

    bool q2 = askDeductionQuestion(
        "최종 추리 2",
        "본관 CCTV실은 일반 학생이 쉽게 들어갈 수 없는 곳이다. 범인은 어떤 방법으로 CCTV실에 접근했을까? ",
        "제갈현철 교수의 잃어버린 마스터키를 사용했다",
        "쇠지레로 정문을 부수고 들어갔다.",
        "경비원을 속여 문을 열게 했다",
        '1'
    );

    if (!q2) {
        showDeductionFail();
        return;
    }

    bool q3 = askDeductionQuestion(
        "최종 추리 3",
        "청금석은 작고 가벼운 물건이 아니었다. 현장에서 범행 방식을 보여주는 흔적은? ",
        "바닥의 긁힌 자국과 발자국",
        "피 묻은 면장갑",
        "코인 사채 독촉 문자",
        '1'
    );

    if (!q3) {
        showDeductionFail();
        return;
    }

    bool q4 = askDeductionQuestion(
        "최종 추리 4",
        "수사는 처음 송우진을 향하고 있었다. 하지만 송우진을 범인으로 단정할 수 없는 이유는 ? ",
        "송우진은 돈이 전혀 필요하지 않았다.",
        "송우진은 범행 시각에 과방에 있었다는 정황이 있다.",
        "송우진은 청금석의 존재를 몰랐다.",
        '2'
    );

    if (!q4) {
        showDeductionFail();
        return;
    }

    system("cls");

    cout << "\n\n\t[ 최종 범인 지목 ]\n\n";
    cout << "\t단서들이 하나의 결론을 가리키고 있다.\n";
    cout << "\t청금석을 훔친 진범은 누구인가?\n\n";

    cout << "\t1. 송우진\n";
    cout << "\t2. 박보승\n";
    cout << "\t3. 경비원\n";
    cout << "\t4. 제갈현철 교수\n";

    cout << "\n\t범인을 선택하세요. ESC: 취소\n";

    char culprit = getNumberChoice('1', '4');

    if (culprit == 27) {
        system("cls");
        return;
    }

    system("cls");

    if (culprit == '4') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

        cout << "\n\n\t[ 추리 성공 ]\n\n";
        cout << "\t범인은 제갈현철 교수였다.\n";
        cout << "\t그는 청금석 내부의 초전도체 성분을 노리고,\n";
        cout << "\t마스터키와 경비실의 혼란을 이용해 청금석을 빼돌렸다.\n\n";
        cout << "\t송우진은 돈 문제 때문에 의심받았지만,\n";
        cout << "\t실제 범행 시각에는 과방에 있었다.\n\n";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        cout << "\t(Enter 또는 ESC를 누르면 엔딩으로 이동합니다.)";

        while (true) {
            if (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
                GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                while (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
                    GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                    Sleep(10);
                }
                break;
            }

            Sleep(10);
        }
        state = ENDING;
    }
    else {
        system("cls");

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

        cout << "\n\n\t[ 추리 실패 ]\n\n";
        cout << "\t당신은 잘못된 사람을 범인으로 지목했다.\n";
        cout << "\t그 틈에 진범은 남은 증거를 없애고 사라졌다.\n\n";
        cout << "\t청금석 사건은 미궁 속으로 빠지고 말았다.\n";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        cout << "\n\t(Enter 또는 ESC를 누르면 배드 엔딩으로 이동합니다.)";

        while (true) {
            if (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
                GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                while (GetAsyncKeyState(VK_RETURN) & 0x8000 ||
                    GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                    Sleep(10);
                }
                break;
            }

            Sleep(10);
        }

        state = BAD_ENDING;
    }
}