#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "screen.h"
#include "util.h"

int Initialize();
int Release();
int DrawBuffer(int DeltaTime);
void HandleInput();

// ���� ������Ʈ�� 0�� �� ������ ���� ����
int GameState;
int GameStartSnakeLength;
int ActiveSnakeNum;
int SnakeDirection; // 0: ����, 1: ������, 2: �Ʒ���, 3: ����

#define MAX_SNAKE_LENGTH 1400
struct GameObject
{
    int posX;
    int posY;
    int isActive;
};

// 0���� �Ӹ�
struct GameObject snakeSkin[MAX_SNAKE_LENGTH];
struct GameObject apple;

int main()
{
    CHECKERROR(Initialize());

    unsigned long time_end = GetTickCount();
    unsigned long deltaTime = GetTickCount();

    while (GameState)
    {
        deltaTime = GetTickCount() - time_end;
        time_end = GetTickCount();

        HandleInput(); // Ű �Է� ó��
        DrawBuffer(deltaTime);

        if (deltaTime < 33)
            Sleep(33 - deltaTime);
    }

    CHECKERROR(Release());

    exit(1);
    return 0;
}

void HandleInput()
{
    if (GetAsyncKeyState(0x41) & 0x8000) // 'A' Ű
    {
        SnakeDirection = (SnakeDirection + 3) % 4; // �������� 90�� ȸ��
    }
    else if (GetAsyncKeyState(0x44) & 0x8000) // 'D' Ű
    {
        SnakeDirection = (SnakeDirection + 1) % 4; // ���������� 90�� ȸ��
    }

}

void InitApple()
{
    // apple �ʱ�ȭ
    srand(time(NULL));
    apple.posX = rand() % 70;
    apple.posY = rand() % 20;
    apple.isActive = 1;
}

int Initialize()
{
    GameState = 1;
    GameStartSnakeLength = 3;
    ActiveSnakeNum = GameStartSnakeLength;
    setScreenSize(70, 20);
    setCursorVisibility(0);
    SetColor(0b1000, 0b1111);
    ClearBuffer();

    // GameObject �ʱ�ȭ

    // ��� �ʱ�ȭ
    InitApple();
    int i = 0;
    while (i < GameStartSnakeLength)
    {
        if (snakeSkin[i].posX == apple.posX && snakeSkin[i].posY == apple.posY)
        {
            InitApple();
            i = 0;
        }
        else
        {
            i = i + 1;
        }
    }

    // �� ���׾Ƹ� �ʱ�ȭ
    i = 0;
    while (i < MAX_SNAKE_LENGTH)
    {
        snakeSkin[i].posX = 35;
        snakeSkin[i].posY = 10;
        snakeSkin[i].isActive = 0;
        i = i + 1;
    }

    i = 0;
    while (i < GameStartSnakeLength)
    {
        snakeSkin[i].posX = 35 - i;
        snakeSkin[i].posY = 10;
        snakeSkin[i].isActive = 1;
        i = i + 1;
    }

    SnakeDirection = 1; // �ʱ� ������ ���������� ����

    return 0;
}

int Release()
{
    return 0;
}

void MoveSnake()
{
    // ���� �̵� �κ�
    int i = GameStartSnakeLength - 1;
    while (i > 0)
    {
        snakeSkin[i].posX = snakeSkin[i - 1].posX;
        snakeSkin[i].posY = snakeSkin[i - 1].posY;
        i = i - 1;
    }

    // �Ӹ� �̵� �κ�
    switch (SnakeDirection)
    {
    case 0: // �������� �̵�
        snakeSkin[0].posY = snakeSkin[0].posY - 1;
        break;
    case 1: // ���������� �̵�
        snakeSkin[0].posX = snakeSkin[0].posX + 1;
        break;
    case 2: // �Ʒ������� �̵�
        snakeSkin[0].posY = snakeSkin[0].posY + 1;
        break;
    case 3: // �������� �̵�
        snakeSkin[0].posX = snakeSkin[0].posX - 1;
        break;
    }
}

int MoveInterval = 500;
int DeltaTimeSum = 0;

int DrawBuffer(int DeltaTime)
{
    setCursorPos(0, 0);
    SetColor(0b1111, 0b0000);
    printf("%s", ScreenBuffer);

    DeltaTimeSum = DeltaTimeSum + DeltaTime;
    if (DeltaTimeSum >= MoveInterval)
    {
        HandleInput();  // Ű �Է� ó��
        MoveSnake();
        DeltaTimeSum = 0;
    }

    // apple
    setCursorPos(apple.posX, apple.posY);
    SetColor(0b1111, 0b0100);
    printf("*");

    // snake
    int i = 0;
    while (i < GameStartSnakeLength)
    {
        setCursorPos(snakeSkin[i].posX, snakeSkin[i].posY);
        SetColor(0b1111, 0b0010);
        printf("O");
        i = i + 1;
    }

    SetColor(0b0000, 0b1111);
    setCursorPos(0, 22);
    if (DeltaTime != 0)
        printf("time : %d                 \nfps :%d                  \n", DeltaTime, 1000 / DeltaTime);

    return 0;
}