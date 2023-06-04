#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <Windows.h>

const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

#define KEY_ESC 27 //아스키코드를 ESC로 정의
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_ENTER 13 

//색 코드(외울 필요 없음)
#define ANSI_COLOR_RED      "\x1b[31m" //바로 앞 문자열에 반영된다.
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"


//커서 지우기
void SetcursorState(bool visible)
{
    CONSOLE_CURSOR_INFO consoleCursorInfo;
    consoleCursorInfo.bVisible = visible;
    consoleCursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
}

void Gotoxy(int x, int y)
{
    //x, y 좌표 설정
    COORD pos = { x,y };
    //커서 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Point {
public:
    int x;
    int y;

    Point(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}
};

class Snake
{
public:
    int x;
    int y;
    int direction; // 뱀의 방향
    bool isAlive;
    Scene& scene;  // Scene 멤버 변수 추가
    std::vector<Point> tail;  // tail 멤버 변수 추가

public:

    Snake(int startX, int startY);

    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();

    bool isAlive;
    void CheckCollision();
};

class Object
{
public:
    void Render(char* screenBuf) const;
};

class Scene
{
public:
    int width;
    int height;
    std::vector<Object> objList;

    char* screenBuf;

    Scene(int w, int h);
    ~Scene();

    void Initialize();
    void InitScreenBuf();
    void ReleaseScreenBuf();
    void Draw();
    void ClearScreenBuf();
};

//class Component
//{
//public:
//    void Start();
//    void Update();
//};

void print_title_screen();
void start_game();

#endif