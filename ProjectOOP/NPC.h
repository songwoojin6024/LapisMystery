#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <array>
#include <limits>
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
    virtual int getReward() { return 120; }

    string getName() { return name; }
    string getHint() { return hint; }
    int getFails() { return failCount; }
    void addFail() { failCount++; }
    bool isCleared() { return cleared; }
    void setCleared() { cleared = true; }
};

class LibraryNPC : public NPC {
public:
    LibraryNPC() : NPC("황효빈 학생", "누가 주식이랑 코인투자 실패로 돈이 급하다고 했는데...") {}

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
    EngNPC1() : NPC("서원필 학생", "제갈현철 교수의 잃어버린 마스터키 카드") {}
    void talk() override {
        cout << "\n[" << name << "]: 내 카드 게임 깨면 단서 줄게. 8쌍을 맞춰봐!" << endl;
    }
    bool playGame() override {
		return runCardGame();
    }
};

class EngNPC2 : public NPC {
public:
    EngNPC2() : NPC("정승재 학생", "대형 탑차(화물차) 렌트 영수증") {}
    void talk() override {
        cout << "\n[" << name << "]: 가위바위보 한 판 해봐. 이기면 단서 줄게." << endl;
    }
    bool playGame() override {
        srand((unsigned int)time(nullptr));

        while (true) {
            cout << "\n>> 가위바위보!" << endl;
            cout << "   1) 가위" << endl;
            cout << "   2) 바위" << endl;
            cout << "   3) 보" << endl;
            cout << "\n>> 선택 (1/2/3): ";

            char key = getChoiceKey("123");
            int player = key - '0';
            int computer = (rand() % 3) + 1;

            string choices[] = { "", "가위", "바위", "보" };
            cout << key << endl;
            cout << "\n나: " << choices[player] << "  vs  상대: " << choices[computer] << endl;

            bool win = (player == 1 && computer == 3) ||
                (player == 2 && computer == 1) ||
                (player == 3 && computer == 2);
            bool draw = (player == computer);

            if (draw) {
                cout << "비겼습니다! 다시 합니다..." << endl;
                Sleep(1000);
                continue;
            }
            else if (win) {
                cout << "이겼습니다!" << endl;
                return true;
            }
            else {
                cout << "졌습니다..." << endl;
                return false;
            }
        }
    }
};

class EngNPC3 : public NPC {
public:
    EngNPC3() : NPC("양정아 학생", "진흙이 묻은 280mm 군용 작업화") {}
    void talk() override {
        cout << "\n[" << name << "]: 사다리타기로 승부 보자. 운이 좋으면 단서 줄게!" << endl;
    }
    bool playGame() override {
        srand((unsigned int)time(nullptr));

        // 결과 배열 - 4개 중 1개만 당첨
        int results[4] = { 0, 0, 0, 0 };
        int win = rand() % 4;
        results[win] = 1;

        cout << "\n>> 사다리타기! 1~4 중 하나를 선택하세요." << endl;
        cout << "\n";
        cout << "  1    2    3    4  " << endl;
        cout << "  |    |    |    |  " << endl;
        cout << "  |____|    |    |  " << endl;
        cout << "  |    |____|    |  " << endl;
        cout << "  |    |    |____|  " << endl;
        cout << "  |    |    |    |  " << endl;
        cout << "  ?    ?    ?    ?  " << endl;
        cout << "\n>> 선택 (1/2/3/4): ";

        char key = getChoiceKey("1234");
        int choice = key - '0' - 1; // 0~3 인덱스로 변환
        cout << key << endl;

        Sleep(500);
        cout << "\n결과 공개!" << endl;
        cout << "  1    2    3    4  " << endl;
        cout << "  |    |    |    |  " << endl;
        cout << "  |____|    |    |  " << endl;
        cout << "  |    |____|    |  " << endl;
        cout << "  |    |    |____|  " << endl;
        cout << "  |    |    |    |  " << endl;

        // 결과 출력
        for (int i = 0; i < 4; i++) {
            if (results[i] == 1) cout << "  ★  ";
            else                 cout << "  ✗  ";
        }
        cout << endl;

        Sleep(500);
        if (results[choice] == 1) {
            cout << "\n당첨입니다!" << endl;
            return true;
        }
        else {
            cout << "\n꽝입니다..." << endl;
            return false;
        }
    }
};

class EngNPC4 : public NPC {
public:
    EngNPC4() : NPC("이름 모를 교수님", "송우진의 코인 사채 독촉 문자") {}
    void talk() override {
        cout << "\n[" << name << "]: 내 수업 시간을 방해하다니. 게임에서 이기면 봐주지." << endl;
        cout << "[" << name << "]: 1~21까지 번갈아 숫자를 부른다. 한 번에 1~3개씩 부를 수 있어." << endl;
        cout << "[" << name << "]: 21을 부르는 사람이 지는 거야." << endl;
    }
    bool playGame() override {
        int count = 0;

        cout << "\n>> 카운팅 게임 시작! 21을 부르면 집니다." << endl;
        cout << ">> 한 번에 1~3개씩 부를 수 있어요." << endl;

        while (true) {
            // 플레이어 차례
            cout << "\n현재 숫자: " << count << endl;
            cout << ">> 몇 개 부를까요? (1/2/3): ";
            char key = getChoiceKey("123");
            int playerCall = key - '0';
            cout << key << endl;

            for (int i = 1; i <= playerCall; i++) {
                count++;
                cout << count << " ";
            }
            cout << endl;

            if (count >= 21) {
                cout << "\n21을 불렀습니다! 당신이 졌어요..." << endl;
                return false;
            }
            int remaining = 21 - count;
            int computerCall;

            if (remaining % 4 == 0) computerCall = 3;
            else if (remaining % 4 == 1) computerCall = 3;
            else computerCall = (remaining % 4) - 1;

            if (computerCall < 1) computerCall = 1;
            if (computerCall > 3) computerCall = 3;

            cout << "교수님: ";
            for (int i = 1; i <= computerCall; i++) {
                count++;
                cout << count << " ";
                Sleep(300);
            }
            cout << endl;

            if (count >= 21) {
                cout << "\n교수님이 21을 불렀습니다! 당신이 이겼어요!" << endl;
                return true;
            }
        }
    }
};

class EngNPC5 : public NPC {
private:
    char board[10];
    char turn;

public:
    EngNPC5() : NPC("박성현 학생", "쇠지레(빠루)와 공구 세트") {
        resetBoard();
    }

    void talk() override {
        cout << "\n[" << name << "]: 나랑 틱택토 한 판 하자." << endl;
        cout << "이기면 단서를 줄게. 비기면 다시 해야 한다." << endl;
    }

    bool playGame() override {
        while (true) {
            resetBoard();
            turn = 'O'; // 컴퓨터 먼저 시작

            system("cls");
            cout << "\n>> [틱택토 게임]" << endl;
            cout << ">> 사용자: X / 컴퓨터: O" << endl;
            cout << ">> 1~9 숫자로 칸을 선택하세요." << endl;
            cout << ">> 무승부면 다시 시작합니다.\n" << endl;

            drawBoard();

            while (true) {
                int loc;

                if (turn == 'O') {
                    cout << "\n> 컴퓨터(O)의 차례입니다." << endl;
                    Sleep(700);

                    loc = getComputerMove();
                    board[loc] = 'O';

                    cout << "컴퓨터가 " << loc << "번 칸을 선택했습니다." << endl;
                }
                else {
                    cout << "\n> 사용자(X)의 차례입니다." << endl;
                    loc = getUserMove();
                    board[loc] = 'X';
                }

                system("cls");
                cout << "\n>> [틱택토 게임]" << endl;
                cout << ">> 사용자: X / 컴퓨터: O\n" << endl;
                drawBoard();

                if (checkForWin(turn)) {
                    if (turn == 'X') {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << "\n사용자 승리!" << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                        Sleep(1000);
                        return true;
                    }
                    else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                        cout << "\n컴퓨터 승리..." << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                        Sleep(1000);
                        return false;
                    }
                }

                if (checkForTie()) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    cout << "\n무승부입니다. 다시 시작합니다." << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    Sleep(1500);
                    break; // 안쪽 while 탈출 후 바깥 while에서 리게임
                }

                turn = (turn == 'O') ? 'X' : 'O';
            }
        }
    }

private:
    void resetBoard() {
        for (int i = 1; i <= 9; i++) {
            board[i] = ' ';
        }
    }

    void drawBoard() const {
        cout << "\n";
        cout << " " << cellText(1) << " | " << cellText(2) << " | " << cellText(3) << endl;
        cout << "---+---+---" << endl;
        cout << " " << cellText(4) << " | " << cellText(5) << " | " << cellText(6) << endl;
        cout << "---+---+---" << endl;
        cout << " " << cellText(7) << " | " << cellText(8) << " | " << cellText(9) << endl;
        cout << "\n";
    }

    char cellText(int i) const {
        if (board[i] == ' ') {
            return '0' + i;
        }

        return board[i];
    }

    bool checkForWin(char p) const {
        return
            (board[1] == p && board[2] == p && board[3] == p) ||
            (board[4] == p && board[5] == p && board[6] == p) ||
            (board[7] == p && board[8] == p && board[9] == p) ||
            (board[1] == p && board[4] == p && board[7] == p) ||
            (board[2] == p && board[5] == p && board[8] == p) ||
            (board[3] == p && board[6] == p && board[9] == p) ||
            (board[1] == p && board[5] == p && board[9] == p) ||
            (board[3] == p && board[5] == p && board[7] == p);
    }

    bool isFree(int i) const {
        return board[i] == ' ';
    }

    bool checkForTie() const {
        for (int i = 1; i <= 9; i++) {
            if (isFree(i)) {
                return false;
            }
        }

        return true;
    }

    int getUserMove() {
        int loc;

        while (true) {
            cout << "1부터 9 사이의 숫자 입력: ";
            cin >> loc;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "숫자를 입력해야 합니다." << endl;
                continue;
            }

            cin.ignore(10000, '\n');

            if (loc < 1 || loc > 9) {
                cout << "1~9 사이의 숫자를 입력해야 합니다." << endl;
                continue;
            }

            if (!isFree(loc)) {
                cout << "이미 선택된 칸입니다." << endl;
                continue;
            }

            return loc;
        }
    }

    int getComputerMove() {
        // 컴퓨터가 바로 이길 수 있으면 그 칸 선택
        for (int i = 1; i <= 9; i++) {
            if (isFree(i)) {
                board[i] = 'O';
                if (checkForWin('O')) {
                    board[i] = ' ';
                    return i;
                }
                board[i] = ' ';
            }
        }

        // 사용자가 바로 이길 수 있으면 막기
        for (int i = 1; i <= 9; i++) {
            if (isFree(i)) {
                board[i] = 'X';
                if (checkForWin('X')) {
                    board[i] = ' ';
                    return i;
                }
                board[i] = ' ';
            }
        }

        // 코너 우선
        int corners[] = { 1, 3, 7, 9 };
        for (int i = 0; i < 4; i++) {
            if (isFree(corners[i])) {
                return corners[i];
            }
        }
        // 중앙
        if (isFree(5)) {
            return 5;
        }
        // 변
        int sides[] = { 2, 4, 6, 8 };
        for (int i = 0; i < 4; i++) {
            if (isFree(sides[i])) {
                return sides[i];
            }
        }

        return 1;
    }
};
class EngNPC6 : public NPC {
public:
    EngNPC6() : NPC("교수의 조교", "청금석 내부 초전도체 성분 분석표") {}

    void talk() override {
        cout << "\n[" << name << "]: 자료가 필요하다고?" << endl;
        cout << "행맨 암호를 풀면 자료 결과를 보여줄게." << endl;
    }

    char getAlphabetKey() {
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

        while (true) {
            for (char c = 'A'; c <= 'Z'; c++) {
                if (GetAsyncKeyState(c) & 0x8000) {
                    while (GetAsyncKeyState(c) & 0x8000) {
                        Sleep(10);
                    }
                    return c;
                }
            }

            Sleep(10);
        }
    }

    bool playGame() override {
        string word = "LAPIS";
        string guessed = "";
        int wrong = 0;
        const int maxWrong = 6;

        while (wrong < maxWrong) {
            system("cls");

            cout << "\n>> [행맨 게임: 청금석 분석 암호]" << endl;
            cout << ">> 힌트: 도난당한 보석의 영어 이름" << endl;
            cout << ">> 알파벳 키를 눌러 정답을 맞히세요." << endl;

            cout << "\n단어: ";
            bool complete = true;

            for (char ch : word) {
                if (guessed.find(ch) != string::npos) {
                    cout << ch << " ";
                }
                else {
                    cout << "_ ";
                    complete = false;
                }
            }

            cout << "\n\n틀린 횟수: " << wrong << " / " << maxWrong << endl;
            cout << "입력한 글자: " << guessed << endl;

            if (complete) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n정답! 분석표 잠금이 해제되었습니다." << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                Sleep(1000);
                return true;
            }

            cout << "\n알파벳 입력: ";
            char key = getAlphabetKey();
            cout << key << endl;

            if (guessed.find(key) != string::npos) {
                cout << "이미 입력한 글자입니다." << endl;
                Sleep(800);
                continue;
            }

            guessed += key;

            if (word.find(key) == string::npos) {
                wrong++;
                cout << "틀렸습니다!" << endl;
            }
            else {
                cout << "맞았습니다!" << endl;
            }

            Sleep(800);
        }

        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\n[실패] 분석표 잠금 해제에 실패했습니다." << endl;
        cout << "정답은 " << word << "였습니다." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        Sleep(1000);

        return false;
    }
};
class MAINBNPC : public NPC {
public:
    MAINBNPC() : NPC("경비실 금고", "경비실 금고 속 출처를 알 수 없는 현금 뭉치") {}

    void talk() override {
        cout << "\n[" << name << "]: 금고 비밀번호는 1부터 100 사이의 숫자다." << endl;
        cout << "6번 안에 맞히면 안에 든 것을 가져가도 좋다." << endl;
    }

    int getReward() override {
        return 50000;
    }

    bool playGame() override {
        srand((unsigned int)time(nullptr));

        int answer = rand() % 100 + 1;
        int tries = 5;

        cout << "\n>> [경비실 금고 해킹]" << endl;
        cout << ">> 1부터 100 사이의 비밀번호를 맞히세요." << endl;
        cout << ">> 기회는 총 5번입니다.\n" << endl;

        for (int i = 1; i <= tries; i++) {
            int guess;

            cout << "\n[" << i << "/" << tries << "] 숫자 입력: ";
            cin >> guess;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "숫자만 입력하세요!" << endl;
                i--;
                continue;
            }

            cin.ignore(10000, '\n');

            if (guess == answer) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n정답! 금고가 열렸습니다." << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                return true;
            }
            else if (guess < answer) {
                cout << "UP! 더 큰 숫자입니다." << endl;
            }
            else {
                cout << "DOWN! 더 작은 숫자입니다." << endl;
            }
        }

        cout << "\n비밀번호 해킹에 실패했습니다. 정답은 " << answer << "였습니다." << endl;
        return false;
    }
};