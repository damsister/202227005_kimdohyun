#include <stdio.h>
#include <time.h>
#include <Windows.h> //Sleep�� �ʿ���
#include "screen.h"
#include "util.h"

int Initialize();
int Release();
int DrawBuffer();


int GameState = 0;

int main()
{
	int isGameRunning = 1;

	CHECKERROR(Initialize()); //Initialize�ȿ��� ����üũ�� �ض�

	unsigned long time_end = GetTickCount();
	//TickCount: CPU�� ȸ�ΰ� �� �� ���ư����� ����
	unsigned long deltaTime = GetTickCount();

	while (isGameRunning)
	{

		SetColor(0b1000, 0b1111);

		WriteToBuffer(25, 10, "������ ������ ����");
		WriteToBuffer(25, 12, "1. ���ӽ���");
		WriteToBuffer(25, 13, "2. ��������");

		DrawBuffer();
		deltaTime = GetTickCount() - time_end;
		time_end = GetTickCount();

		//1000/60 = 16.66666667 60������
		if (deltaTime < 17)
			Sleep(17 - deltaTime); //���� �ð� ���� �����

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