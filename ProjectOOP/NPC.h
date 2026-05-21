#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include"CardGame.h"
using namespace std;

inline char getChoiceKey(const string& keys) {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    while (true) {
        for (char key : keys) {
            SHORT state = GetAsyncKeyState(toupper(key));

            if (state & 0x8000) {
                while (GetAsyncKeyState(toupper(key)) & 0x8000) {
                    Sleep(10);
                }

                return key;
            }
        }

        Sleep(10);
    }
}

class NPC {
protected:
    string name;
    string hint;
    int failCount;
    bool cleared; // 성공 여부 추가

public:
    NPC(string n, string h) : name(n), hint(h), failCount(0), cleared(false) {}
    virtual ~NPC() {}

    virtual void talk() = 0;
    virtual bool playGame() = 0;

    string getName() { return name; }
    string getHint() { return hint; }
    int getFails() { return failCount; }
    void addFail() { failCount++; }
    bool isCleared() { return cleared; }
    void setCleared() { cleared = true; }
};

class LibraryNPC : public NPC {
public:
    LibraryNPC() : NPC("공부벌레", "범인은 안경을 썼어!") {}

    void talk() override {
        cout << "\n[" << name << "]: 공부 방해하지 말고 비켜! 나를 이기면 정보를 주지." << endl;
    }

    bool playGame() override {
        cout << "\n>> 넌센스 퀴즈: 세상에서 가장 가난한 왕은?" << endl;
        cout << "\n   a) 거지왕" << endl;
        cout << "   b) 최저임금" << endl;
        cout << "   c) 빈곤왕" << endl;
        cout << "\n>> 답을 입력하세요 (a/b/c): ";
        char key = getChoiceKey("abc");
        cout << key << endl;
        return (key == 'b');
    }
};

class EngNPC1 : public NPC {
public:
    EngNPC1() : NPC("강의실 학생1", "힌트1") {}
    void talk() override {
        cout << "\n[" << name << "]: 내 카드 게임 깨면 단서 줄게. 8쌍을 맞춰봐!" << endl;
    }
    bool playGame() override {
		return runCardGame();
    }
};

class EngNPC2 : public NPC {
public:
    EngNPC2() : NPC("강의실 학생2", "힌트2") {}
    void talk() override {
        cout << "\n[" << name << "]: 나랑 게임 한 판 해봐." << endl;
    }
    bool playGame() override {
        cout << ">> 1.가위  2.바위  3.보 (번호 키 누르기): ";
        char key = getChoiceKey("123");
        cout << key << endl;
        int choice = key - '0';
        return (choice != 1);
    }
};

class EngNPC3 : public NPC {
public:
    EngNPC3() : NPC("강의실 학생3", "힌트3") {}
    void talk() override {
        cout << "\n[" << name << "]: 나랑 게임 한 판 해봐." << endl;
    }
    bool playGame() override {
        cout << ">> 1.가위  2.바위  3.보 (번호 키 누르기): ";
        char key = getChoiceKey("123");
        cout << key << endl;
        int choice = key - '0';
        return (choice != 1);
    }
};

class EngNPC4 : public NPC {
public:
    EngNPC4() : NPC("교수님", "힌트4") {}
    void talk() override {
        cout << "\n[" << name << "]: 나랑 게임 한 판 해봐." << endl;
    }
    bool playGame() override {
        cout << ">> 1.가위  2.바위  3.보 (번호 키 누르기): ";
        char key = getChoiceKey("123");
        cout << key << endl;
        int choice = key - '0';
        return (choice != 1);
    }
};

class EngNPC5 : public NPC {
public:
    EngNPC5() : NPC("과방 선배", "힌트5") {}
    void talk() override {
        cout << "\n[" << name << "]: 나랑 게임 한 판 해봐." << endl;
    }
    bool playGame() override {
        cout << ">> 1.가위  2.바위  3.보 (번호 키 누르기): ";
        char key = getChoiceKey("123");
        cout << key << endl;
        int choice = key - '0';
        return (choice != 1);
    }
};