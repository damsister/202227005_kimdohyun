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

//게임 스테이트가 0일때 무조건 종료
int GameState = 0;

//0번이 머리

struct SnakeBody skin[BODY_LENGTH];
struct Apple apple;
struct Player player;

int snakeBodyLength = 2;
int MovingTime = 1000;
int deltaTimeSum = 0;


int main()
{
	int isGameRunning = 1; //0이 되면 게임 종료
	
	CHECKERROR(Initialize()); //Initialize안에서 에러체크를 해라
	
	unsigned long time_end = GetTickCount();
	unsigned long deltaTime = GetTickCount();
	//GetTickCount: CPU의 회로가 몇 번 돌아갔는지 측정

	while(isGameRunning)
	{
		DrawBuffer(deltaTime);
		deltaTime = GetTickCount() - time_end;
		time_end = GetTickCount();
		//1000/33 = 30.3030303030303 30프레임
		if(deltaTime < 33)
			Sleep(33- deltaTime); //남은 시간 동안 쉬어라
	}

	CHECKERROR(Release());

	exit(1);
	return 0;
}

void initApplePos()
{
	srand(time(NULL));

	//사과 데이터 초기화
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
			//rand함수를 하면 항상 같은 값이 출력
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
	//게임 상태
	GameState = 0;
	deltaTimeSum = 0;
	MovingTime = 300;
	
	//플레이어 초기화
	player.posX = 35;
	player.posY = 10;

	//뱀 데이터 초기화
	snakeBodyLength = 2;
	int i = 0;
	while(i< BODY_LENGTH)
	{
		skin[i].active = 0;
		skin[i].posX = player.posX;
		skin[i].posY = player.posY;

		i = i+1;
	}	
	
	//사과(GameObject) 초기화
	initApplePos();

	//사용할 뱀 데이터 초기화
	snakeBodyLength = 2;
	i = 0;
	while (i < snakeBodyLength)
	{
		skin[i].active = 1;
		skin[i].posX = player.posX;
		skin[i].posY = player.posY - i;

		i = i + 1;
	}

	//화면 초기화
	setScreenSize(70, 20);	
	setCursorIcon(0);
	ClearBuffer();	

	return 0;
}

int Release()
{
	return 0;
}

//dir: 좌,우
void MoveSnake(int dir)
{

}

int DrawBuffer(int DeltaTime)
{
	//배경 그리기
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
		//몸통이동 부분
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


	//뱀 그리기
	SetColor(0b0000, 0b1010);	
	int i = snakeBodyLength-1;
	while (i >= 0)
	{
		setCursorPos(skin[i].posX, skin[i].posY);
		printf("#");
		i = i - 1;
	}

	//사과 그리기
	setCursorPos(apple.posX, apple.posY);
	SetColor(0b0000, 0b0100); //배경색: 흰색, 사과: 빨간색

	printf("*");

	//색상 초기화
	SetColor(0b0000, 0b0111);
	setCursorPos(0, 22);
	if (DeltaTime != 0)
		printf("Delta Time : %d              \nfps :%d\n          ", DeltaTime, 1000 / DeltaTime);

	return 0;
}