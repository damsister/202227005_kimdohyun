#include "game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, percentX, percentY, caretX, caretY, score, collisitionCount;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
bool promoted = false; //���� ���θ� ��Ÿ���� ���� �߰�
string ranks;

// �� ���� �迭 ����
char buffer[height][width];
char oldBuffer[height][width];

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2; //���� �ʱ� ��ġ
    y = height / 2; //���� �ʱ� ��ġ
    fruitX = rand() % width; //0(��)
    fruitY = rand() % height; //0(��)
    caretX = rand() % width; //^(������ ������ ��ֹ�)
    caretY = rand() % height; //^(������ ������ ��ֹ�)
    score = 0;
    ranks = "����";
    collisitionCount = 4;

    // ���� ���� �ʱ�ȭ
    nTail = 0;
    for (int i = 0; i < 100; i++)
    {
        tailX[i] = 0;
        tailY[i] = 0;
    }
}

void Print_title()
{
    cout << ANSI_COLOR_RESET"****************************************" << endl;
    cout << ANSI_COLOR_RESET"*                                      *" << endl;
    cout << ANSI_COLOR_RESET"*                                      *" << endl;
    cout << ANSI_COLOR_RESET"*          �챺�� �� ����ì��          *" << endl;
    cout << ANSI_COLOR_RESET"*                                      *" << endl;
    cout << ANSI_COLOR_RESET"*            1. ���� ����              *" << endl;
    cout << ANSI_COLOR_RESET"*            2. ���� ����              *" << endl;
    cout << ANSI_COLOR_RESET"*           ���� ���� (esc)            *" << endl;
    cout << ANSI_COLOR_RESET"*                                      *" << endl;
    cout << ANSI_COLOR_RESET"****************************************" << endl;
    cout << ANSI_COLOR_RESET"    �� ���� ì�ܼ� �����ؾ���!" << endl;
}

int Introduction()
{
    cout << ANSI_COLOR_RESET"******************************************" << endl;
    cout << ANSI_COLOR_RESET"*         ���� ����ȭ���Դϴ�.           *" << endl;
    cout << ANSI_COLOR_RESET"*         0 -> ���� : +5, �� : +1        *" << endl;
    cout << ANSI_COLOR_RESET"*         % -> ���� : -3, �� : -1        *" << endl;
    cout << ANSI_COLOR_RESET"*         % -> 4�� ������ ���ӿ���       *" << endl;
    cout << ANSI_COLOR_RESET"*         ^ -> ���ӿ���                  *" << endl;
    cout << ANSI_COLOR_RESET"******************************************" << endl;
    cout << ANSI_COLOR_RESET"*   Ÿ��Ʋȭ������ ���ư����? (Y/N)     *" << endl;
    cout << ANSI_COLOR_RESET"******************************************" << endl;
    return 0;
}

int GameOver()
{
    system("cls");
    cout << ANSI_COLOR_RESET"****************************************" << endl;
    cout << ANSI_COLOR_RESET"              ���� ����!" << endl;
    cout << ANSI_COLOR_RESET"              " << endl;
    cout << ANSI_COLOR_RESET"              ����: " << score << endl;
    cout << ANSI_COLOR_RESET"              ���� :" << ranks << endl;
    cout << ANSI_COLOR_RESET"              " << endl;
    cout << ANSI_COLOR_RESET"       ������ �����Ͻðڽ��ϱ�? (Y/N) " << endl;
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
        Print_title();
    }
    else
    {
        GameOver(); // �߸��� �Է��̸� �ٽ� GameOver �Լ� ȣ��
    }
    return 0;
}

int GameOver1()
{
    system("cls");
    cout << ANSI_COLOR_RESET"****************************************" << endl;
    cout << ANSI_COLOR_RESET"        �ӿ����� �� ���� �����մϴ�~~~" << endl;
    cout << ANSI_COLOR_RESET"              " << endl;
    cout << ANSI_COLOR_RESET"              ����: " << score << endl;
    cout << ANSI_COLOR_RESET"              " << endl;
    cout << ANSI_COLOR_RESET"       ������ �����Ͻðڽ��ϱ�? (Y/N) " << endl;
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
        Print_title();
    }
    else
    {
        GameOver(); // �߸��� �Է��̸� �ٽ� GameOver �Լ� ȣ��
    }
    return 0;
}

void Draw()
{
    SetcursorState(false); // Ŀ�� �����

    // ���� ��ü
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            if (buffer[i][j] != oldBuffer[i][j]) 
            {
                gotoxy(j, i);
                cout << buffer[i][j];
                oldBuffer[i][j] = buffer[i][j];
            }
        }
    }

    // ȭ�� ������Ʈ
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

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
    cout << ANSI_COLOR_RESET"���� : " << score << "  " << endl;
    cout << ANSI_COLOR_RESET"���� :" << ranks << endl;
    cout << ANSI_COLOR_RESET"�浹 Ƚ�� :" << collisitionCount << endl;
    cout << ANSI_COLOR_RESET"���� ���Ḧ �Ϸ��� ESC�� �����ּ���" << endl;
    cout << ANSI_COLOR_RESET"�Ͻ������� �Ϸ��� Q�� �����ּ���" << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case KEY_LEFT:
            if (dir != RIGHT) // ���� ������ �������� �ƴ� ��쿡�� �������� ����
                dir = LEFT;
            break;
        case KEY_RIGHT:
            if (dir != LEFT) // ���� ������ ������ �ƴ� ��쿡�� ���������� ����
                dir = RIGHT;
            break;
        case KEY_UP:
            if (dir != DOWN) // ���� ������ �Ʒ����� �ƴ� ��쿡�� �������� ����
                dir = UP;
            break;
        case KEY_DOWN:
            if (dir != UP) // ���� ������ ������ �ƴ� ��쿡�� �Ʒ������� ����
                dir = DOWN;
            break;
        case KEY_ESC:
            gameOver = true;
            break;
        case KEY_STOP:
            gotoxy(width / 2 - 5, height / 2);
            cout << ANSI_COLOR_BLUE"�Ͻ�����" << endl;
            while (true)
            {
                if (_kbhit())
                {
                    char resumeKey = _getch();
                    if (resumeKey == 'q' || resumeKey == 'Q')
                    {
                        gotoxy(width / 2 - 5, height / 2);
                        cout << "          " << endl; // �Ͻ����� �޽��� �����
                        break; // �Ͻ����� ����
                    }
                }
            }
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

    if (x == fruitX && y == fruitY)
    {
        score += 5;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;

        // '^'�� ������ ��ǥ ����
        caretX = rand() % width;
        caretY = rand() % height;
        // '%'�� ������ ��ǥ ����
        percentX = rand() % width;
        percentY = rand() % height;
    }

    // '%'�� ����� �� ���� ���� �� ���� ���� ����
    if (x == percentX && y == percentY)
    {
        score -= 3;
        if (nTail > 0)
            nTail--;
        percentX = rand() % width;
        percentY = rand() % height;
        collisitionCount--;
    }

    if (ranks == "���" || ranks == "����") // �� ���� ��� ���� ���� ������ ����
    {
        promoted = true;
        ranks = "���"; // �Ǵ� "����", ��ȣ�� ���� ����
    }
    else if (ranks == "�븮")
    {
        promoted = false;
        ranks = "����";
    }
    else if (ranks == "����")
    {
        promoted = false;
        ranks = "�븮";
    }
    else if (ranks == "����")
    {
        promoted = false;
        ranks = "����";
    }
    else if (ranks == "����")
    {
        promoted = false;
        ranks = "����";
    }

    if (collisitionCount == 0)
    {
        GameOver();
    }

    // '^'�� ����� �� ���� ����
    if (x == caretX && y == caretY)
    {
        gameOver = true;
    }
}

int main()
{
    Print_title();

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
                    if (score >= 15 && !promoted)
                    {
                        gotoxy(width / 2 - 5, height / 2);
                        ranks = "���";
                        promoted = true; // ���� ���¸� true�� �����Ͽ� �ߺ� ǥ�ø� ����
                    }
                    promoted = false;
                    if (score >= 25 && !promoted)
                    {
                        gotoxy(width / 2 - 5, height / 2);
                        ranks = "����";
                        promoted = true;
                    }
                    promoted = false;
                    if (score >= 40 && !promoted)
                    {
                        gotoxy(width / 2 - 5, height / 2);
                        ranks = "�븮";
                        promoted = true;
                    }
                    promoted = false;
                    if (score >= 55 && !promoted)
                    {
                        gotoxy(width / 2 - 5, height / 2);
                        ranks = "����";
                        promoted = true;
                    }
                    promoted = false;
                    if (score >= 70 && !promoted)
                    {
                        gotoxy(width / 2 - 5, height / 2);
                        ranks = "����";
                        promoted = true;
                    }
                    promoted = false;
                    if (score >= 85 && !promoted)
                    {
                        gotoxy(width / 2 - 5, height / 2);
                        ranks = "����";
                        promoted = true;
                    }
                    promoted = false;
                    if (score >= 105 && !promoted)
                    {
                        GameOver1();
                    }
                    Sleep(50); // ���� �ӵ� ������ ���� ����
                }
                GameOver();
            }
            else if (key == '2')
            {
                system("cls");
                Introduction();
                char choice = _getch();
                if (choice == 'Y' || choice == 'y')
                {
                    system("cls");
                    Print_title();
                }
                else if (choice == 'N' || choice == 'n')
                {
                    system("cls");
                    break;
                }
            }
            else if (key == KEY_ESC)
            {
                // ���� ����
                gotoxy(5, 12);
                cout << ANSI_COLOR_RESET "�����Ͻðڽ��ϱ�?" << endl;
                gotoxy(5, 13);
                cout << ANSI_COLOR_YELLOW "[��]" << endl;
                gotoxy(15, 13);
                cout << ANSI_COLOR_RESET "[�ƴϿ�]  " << endl;

                bool isYesSelected = true;
                while (true) // ESC�� ������ ���� ������ �ݺ��Ѵ�.
                {
                    if (_kbhit()) // Ű �Է� �ޱ�
                    {
                        char key = _getch();

                        if (key == KEY_LEFT || key == KEY_RIGHT) // 'a' �Ǵ� 'd'�� �ԷµǸ� ���õ� �޴��� �����Ѵ�.
                        {
                            isYesSelected = !isYesSelected;

                            // ���õ� �޴��� ���� ����� �Ǵ� �⺻ �������� ����Ѵ�.
                            if (isYesSelected)
                            {
                                gotoxy(5, 13);
                                cout << ANSI_COLOR_YELLOW "[��]  ";
                                gotoxy(15, 13);
                                cout << ANSI_COLOR_RESET "[�ƴϿ�]  ";
                            }
                            else
                            {
                                gotoxy(5, 13);
                                cout << ANSI_COLOR_RESET "[��]  ";
                                gotoxy(15, 13);
                                cout << ANSI_COLOR_YELLOW "[�ƴϿ�]  ";
                            }
                        }
                        else if (key == KEY_ENTER) // Enter�� �ԷµǸ� ���õ� �޴��� ���� �����ϰų� ������ ��� �����Ѵ�.
                        {
                            if (isYesSelected)
                            {
                                exit(0); // ����
                            }
                            else
                            {
                                gotoxy(5, 12);
                                cout << ANSI_COLOR_RESET"                     " << endl; // ���� �޽��� �����
                                gotoxy(5, 13);
                                cout << ANSI_COLOR_RESET"     " << endl; // ���� �޴� �����
                                gotoxy(15, 13);
                                cout << ANSI_COLOR_RESET"        " << endl;
                                system("cls");
                                Print_title();
                                break; // �ݺ��� ����
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
//chrono:��ǻ�� �ý��� �ð�
//startRenderTiemPoint = chrono::system_clock::now(); //����ð��������� 
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

//kbhit()//ȭ���� ���ų� �� �Է��� ���� ����
//���������� 1 -> �Է�
//���������� 0 -> �Է�X
//������ : ���ÿ� ����