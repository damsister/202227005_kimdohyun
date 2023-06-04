#include <stdio.h>
#include <time.h>
#include <Windows.h> //Sleep에 필요함
#include "screen.h"
#include "util.h"

int Initialize();
int Release();
int DrawBuffer();


int GameState = 0;

int main()
{
	int isGameRunning = 1;

	CHECKERROR(Initialize()); //Initialize안에서 에러체크를 해라

	unsigned long time_end = GetTickCount();
	//TickCount: CPU의 회로가 몇 번 돌아갔는지 측정
	unsigned long deltaTime = GetTickCount();

	while (isGameRunning)
	{

		SetColor(0b1000, 0b1111);

		WriteToBuffer(25, 10, "게임의 제목은 없다");
		WriteToBuffer(25, 12, "1. 게임시작");
		WriteToBuffer(25, 13, "2. 게임종료");

		DrawBuffer();
		deltaTime = GetTickCount() - time_end;
		time_end = GetTickCount();

		//1000/60 = 16.66666667 60프레임
		if (deltaTime < 17)
			Sleep(17 - deltaTime); //남은 시간 동안 쉬어라

		if (deltaTime != 0)
			printf("time : %d \nfps :%d\n", deltaTime, 1000 / deltaTime);

	}

	CHECKERROR(Release());

	exit(1);
	return 0; //0: no error 1: error
}

int Initialize()
{
	GameState = 0;
	setScreenSize(70, 20);

	ClearBuffer();

	return 0;
}

int Release()
{
	return 0;
}

int DrawBuffer()
{
	setCursorPos(0, 0);
	printf("%s", ScreenBuffer);
	return 0;
}