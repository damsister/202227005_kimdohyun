#include "game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, percentX, percentY, caretX, caretY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width; //0(공)
    fruitY = rand() % height; //0(공)
    caretX = rand() % width; //^(게임이 끝나는 장애물)
    caretY = rand() % height; //^(게임이 끝나는 장애물)
    score = 0;

    // 뱀의 꼬리 초기화
    nTail = 0;
    for (int i = 0; i < 100; i++)
    {
        tailX[i] = 0;
        tailY[i] = 0;
    }
}

void print_title()
{
    cout << ANSI_COLOR_RESET"****************************************" << endl;
    cout << ANSI_COLOR_RESET"*                                      *" << endl;
    cout << ANSI_COLOR_RESET"*                                      *" << endl;
    cout << ANSI_COLOR_RESET"*          뱀군아 공 가져챙겨          *" << endl;
    cout << ANSI_COLOR_RESET"*                                      *" << endl;
    cout << ANSI_COLOR_RESET"*            1. 게임 시작              *" << endl;
    cout << ANSI_COLOR_RESET"*            2. 게임 설명              *" << endl;
    cout << ANSI_COLOR_RESET"*           게임 종료 (esc)            *" << endl;
    cout << ANSI_COLOR_RESET"*                                      *" << endl;
    cout << ANSI_COLOR_RESET"****************************************" << endl;
    cout << ANSI_COLOR_RESET"    공 많이 챙겨서 승진해야지!"           << endl;
}

int introduction()
{
    cout << ANSI_COLOR_RESET"******************************************" << endl;
    cout << ANSI_COLOR_RESET"*         게임 설명화면입니다.           *" << endl;
    cout << ANSI_COLOR_RESET"*         0 -> 점수 : +10, 공 : +1       *" << endl;
    cout << ANSI_COLOR_RESET"*         % -> 점수 : -8, 공 : -1        *" << endl;
    cout << ANSI_COLOR_RESET"*         ^ -> 게임오버                  *" << endl;
    cout << ANSI_COLOR_RESET"******************************************" << endl;
    cout << ANSI_COLOR_RESET"*   타이틀화면으로 돌아갈까요? (Y/N)     *" << endl;
    cout << ANSI_COLOR_RESET"******************************************" << endl;
    return 0;
}

int GameOver()
{
    system("cls");
    cout << ANSI_COLOR_RESET"****************************************" << endl;
    cout << ANSI_COLOR_RESET"              게임 오버!" << endl;
    cout << ANSI_COLOR_RESET"              " << endl;
    cout << ANSI_COLOR_RESET"              공 개수: " << score << endl;
    cout << ANSI_COLOR_RESET"              "<< endl;
    cout << ANSI_COLOR_RESET"       게임을 종료하시겠습니까? (Y/N) " << endl;
    cout << ANSI_COLOR_RESET"****************************************" << endl;

    char key_input;

    key_input = _getch();

    if (key_input == 'y')
    {
        exit(0);
    }
    else if (key_input == 'n')
    {
        system("cls");
        print_title();
    }
    else
    {
        GameOver(); // 잘못된 입력이면 다시 GameOver 함수 호출
    }
    return 0;
}

void Draw()
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << ANSI_COLOR_GREEN"#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << ANSI_COLOR_GREEN"#";
            }
            if (i == y && j == x)
            {
                cout << ANSI_COLOR_RESET"@";
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << ANSI_COLOR_YELLOW"0";
            }
            else if (i == percentY && j == percentX)
            {
                cout << ANSI_COLOR_CYAN"%";
            }
            else if (i == caretY && j == caretX)
            {
                cout << ANSI_COLOR_RED"^";
            }
            else
            {
                bool printTail = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << ANSI_COLOR_RESET"o";
                        printTail = true;
                    }
                }
                if (!printTail)
                    cout << " ";
            }

            if (j == width - 1)
                cout << ANSI_COLOR_GREEN"#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }

    cout << endl;
    cout << ANSI_COLOR_RESET"공 :" << score << endl;
    cout << ANSI_COLOR_RESET"게임 종료를 하려면 ESC를 눌러주세요" << endl;

}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case KEY_LEFT:
            if (dir != RIGHT) // 현재 방향이 오른쪽이 아닌 경우에만 왼쪽으로 변경
            dir = LEFT;
            break;
        case KEY_RIGHT:
            if (dir != LEFT) // 현재 방향이 왼쪽이 아닌 경우에만 오른쪽으로 변경
            dir = RIGHT;
            break;
        case KEY_UP:
            if (dir != DOWN) // 현재 방향이 아래쪽이 아닌 경우에만 위쪽으로 변경
            dir = UP;
            break;
        case KEY_DOWN:
            if (dir != UP) // 현재 방향이 위쪽이 아닌 경우에만 아래쪽으로 변경
            dir = DOWN;
            break;
        case KEY_ESC:
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= width || x < 0 || y >= height || y < 0)
    {
        gameOver = true;
    }

    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
            break;
        }
    }

    // 뱀이 공을 먹을 때마다 '^' 하나씩 랜덤 생성
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;

        // '^'의 랜덤한 좌표 생성
        caretX = rand() % width;
        caretY = rand() % height;
        // '%'의 랜덤한 좌표 생성
        percentX = rand() % width;
        percentY = rand() % height;
    }

    // '%'에 닿았을 때 점수 감소 및 뱀의 몸통 감소
    if (x == percentX && y == percentY)
    {
        score -= 8;
        if (nTail > 0)
            nTail--;
        percentX = rand() % width;
        percentY = rand() % height;
    }

    // '^'에 닿았을 때 게임 오버
    if (x == caretX && y == caretY)
    {
        gameOver = true;
    }
}


int main()
{
    print_title();

    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();
            if (key == '1')
            {
                system("cls");
                Setup();
                while (!gameOver)
                {
                    Draw();
                    Input();
                    Logic();
                    Sleep(50); // 게임 속도 조절을 위한 지연
                }
                GameOver();
            }
            else if (key == '2')
            {
                system("cls");
                introduction();
                char choice = _getch();
                if (choice == 'Y' || choice == 'y')
                {
                    system("cls");
                    print_title();
                }
                else if (choice == 'N' || choice == 'n')
                {
                    system("cls");
                    break;
                }
            }
            else if (key == KEY_ESC)
            {
                // 게임 종료
                gotoxy(5, 12);
                cout << ANSI_COLOR_RESET "종료하시겠습니까?" << endl;
                gotoxy(5, 13);
                cout << ANSI_COLOR_YELLOW "[예]" << endl;
                gotoxy(15, 13);
                cout << ANSI_COLOR_RESET "[아니오]  " << endl;

                bool isYesSelected = true;
                while (true) // ESC를 눌러서 나갈 때까지 반복한다.
                {
                    if (_kbhit()) // 키 입력 받기
                    {
                        char key = _getch();

                        if (key == KEY_LEFT || key == KEY_RIGHT) // 'a' 또는 'd'가 입력되면 선택된 메뉴를 변경한다.
                        {
                            isYesSelected = !isYesSelected;

                            // 선택된 메뉴에 따라 노란색 또는 기본 색상으로 출력한다.
                            if (isYesSelected)
                            {
                                gotoxy(5, 13);
                                cout << ANSI_COLOR_YELLOW "[예]  ";
                                gotoxy(15, 13);
                                cout << ANSI_COLOR_RESET "[아니오]  ";
                            }
                            else
                            {
                                gotoxy(5, 13);
                                cout << ANSI_COLOR_RESET "[예]  ";
                                gotoxy(15, 13);
                                cout << ANSI_COLOR_YELLOW "[아니오]  ";
                            }
                        }
                        else if (key == KEY_ENTER) // Enter가 입력되면 선택된 메뉴에 따라 종료하거나 게임을 계속 실행한다.
                        {
                            if (isYesSelected)
                            {
                                exit(0); // 종료
                            }
                            else
                            {
                                gotoxy(5, 12);
                                cout << ANSI_COLOR_RESET"                     " << endl; // 종료 메시지 지우기
                                gotoxy(5, 13);
                                cout << ANSI_COLOR_RESET"     " << endl; // 선택 메뉴 지우기
                                gotoxy(15, 13);
                                cout << ANSI_COLOR_RESET"        " << endl;
                                system("cls");
                                print_title();
                                break; // 반복문 종료
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}

//#include <chrono>
//chrono:컴퓨터 시스템 시간
//startRenderTiemPoint = chrono::system_clock::now(); //현재시간가져오는 
//isKeyPressed();

//class Scene
// vector<object>
// sc[000]
//class Object
// vector<commpont>
//class Commpont
//start()
//update()

//transform
//rigidbody : Commpont
// new() -> vector<commpont> push-> cubeobj new()-> vector<object> Scene.Draw->vector<commpont>
//

//kbhit()//화면을 띄우거나 등 입력을 받지 않음
//눌려있으면 1 -> 입력
//떼져있으면 0 -> 입력X
//스레드 : 동시에 시작