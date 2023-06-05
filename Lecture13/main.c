#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "screen.h"
#include "util.h"

struct SnakeBody
{
	int posX;
	int posY;
	int active;
};

struct Apple
{
	int posX;
	int posY;
	int active;
};

struct Player
{
	int posX;
	int posY;	
};

#define BODY_LENGTH 1400

int Initialize();
int Release();
int DrawBuffer(int DeltaTime);

//���� ������Ʈ�� 0�϶� ������ ����
int GameState = 0;

//0���� �Ӹ�

struct SnakeBody skin[BODY_LENGTH];
struct Apple apple;
struct Player player;

int snakeBodyLength = 2;
int MovingTime = 1000;
int deltaTimeSum = 0;


int main()
{
	int isGameRunning = 1; //0�� �Ǹ� ���� ����
	
	CHECKERROR(Initialize()); //Initialize�ȿ��� ����üũ�� �ض�
	
	unsigned long time_end = GetTickCount();
	unsigned long deltaTime = GetTickCount();
	//GetTickCount: CPU�� ȸ�ΰ� �� �� ���ư����� ����

	while(isGameRunning)
	{
		DrawBuffer(deltaTime);
		deltaTime = GetTickCount() - time_end;
		time_end = GetTickCount();
		//1000/33 = 30.3030303030303 30������
		if(deltaTime < 33)
			Sleep(33- deltaTime); //���� �ð� ���� �����
	}

	CHECKERROR(Release());

	exit(1);
	return 0;
}

void initApplePos()
{
	srand(time(NULL));

	//��� ������ �ʱ�ȭ
	apple.active = 0;
	apple.posX = rand() % 70;
	apple.posY = rand() % 20;
	int i = 0;
	while (i < BODY_LENGTH)
	{
		if (skin[i].posX == apple.posX && skin[i].posY == apple.posY)
		{
			apple.posX = rand() % 70;
			apple.posY = rand() % 20;
			//rand�Լ��� �ϸ� �׻� ���� ���� ���
			i = 0;
		}
		else
		{
			i = i + 1;
		}
	}
}


int Initialize()
{
	//���� ����
	GameState = 0;
	deltaTimeSum = 0;
	MovingTime = 300;
	
	//�÷��̾� �ʱ�ȭ
	player.posX = 35;
	player.posY = 10;

	//�� ������ �ʱ�ȭ
	snakeBodyLength = 2;
	int i = 0;
	while(i< BODY_LENGTH)
	{
		skin[i].active = 0;
		skin[i].posX = player.posX;
		skin[i].posY = player.posY;

		i = i+1;
	}	
	
	//���(GameObject) �ʱ�ȭ
	initApplePos();

	//����� �� ������ �ʱ�ȭ
	snakeBodyLength = 2;
	i = 0;
	while (i < snakeBodyLength)
	{
		skin[i].active = 1;
		skin[i].posX = player.posX;
		skin[i].posY = player.posY - i;

		i = i + 1;
	}

	//ȭ�� �ʱ�ȭ
	setScreenSize(70, 20);	
	setCursorIcon(0);
	ClearBuffer();	

	return 0;
}

int Release()
{
	return 0;
}

//dir: ��,��
void MoveSnake(int dir)
{

}

int DrawBuffer(int DeltaTime)
{
	//��� �׸���
	SetColor(0b0000, 0b0111);
	setCursorPos(0, 0);
	printf("%s", ScreenBuffer);
	
	//snake
	if(DeltaTime > 0)
		deltaTimeSum = deltaTimeSum + DeltaTime;

	if (deltaTimeSum >= MovingTime)
	{
		player.posX = player.posX + 1;		
		int i = snakeBodyLength - 1;
		//�����̵� �κ�
		while (i >= 0)
		{
			if (i > 0)
			{
				skin[i].posX = skin[i - 1].posX;
				skin[i].posY = skin[i - 1].posY;
			}
			else
			{
				skin[i].posX = player.posX;
				skin[i].posY = player.posY;
			}
			i = i - 1;
		}		
		deltaTimeSum = 0;
	}


	//�� �׸���
	SetColor(0b0000, 0b1010);	
	int i = snakeBodyLength-1;
	while (i >= 0)
	{
		setCursorPos(skin[i].posX, skin[i].posY);
		printf("#");
		i = i - 1;
	}

	//��� �׸���
	setCursorPos(apple.posX, apple.posY);
	SetColor(0b0000, 0b0100); //����: ���, ���: ������

	printf("*");

	//���� �ʱ�ȭ
	SetColor(0b0000, 0b0111);
	setCursorPos(0, 22);
	if (DeltaTime != 0)
		printf("Delta Time : %d              \nfps :%d\n          ", DeltaTime, 1000 / DeltaTime);

	return 0;
}