#pragma once //��� ������ ����� ���� 
//#define _IS_THIS_HEADER_INCLUDED
#include <iostream>
#include <conio.h>
#include <Windows.h>

#define KEY_ESC 27 //�ƽ�Ű�ڵ带 ESC�� ����
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_ENTER 13 

//�� �ڵ�(�ܿ� �ʿ� ����)
#define ANSI_COLOR_RED      "\x1b[31m" //�ٷ� �� ���ڿ��� �ݿ��ȴ�.
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"


namespace MuSoeun
{
	void gOTOXY(int x, int y) {
		//x, y ��ǥ ����
		COORD pos = { x,y };
		//Ŀ�� �̵�
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	//Ŀ�� �����
	void SEtCursorState(bool visible)
	{
		CONSOLE_CURSOR_INFO consoleCursorInfo;
		consoleCursorInfo.bVisible = visible;
		consoleCursorInfo.dwSize = 1;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
	}

	class MGameLoop
	{
	public : 
		MGameLoop() {} //������
		~MGameLoop() {} //�Ҹ���

		bool isGameRunning = false;

		void Initialize()
		{
			isGameRunning = true;
			gOTOXY(3, 15);
			std::cout << ANSI_COLOR_RESET "���� �ʱ�ȭ ��" << std::endl;
		}

		void Release()
		{
			gOTOXY(3, 18);
			std::cout << ANSI_COLOR_RESET "���� ����" << std::endl;
		}

		void Update()
		{
			gOTOXY(3, 10);
			std::cout << ANSI_COLOR_RESET "���� Ű�Է� ���" << std::endl;
			
			if (_kbhit())
			{
				KeyEvent(_getch()); //�� �Լ��� �޾Ƽ�
			}

		}
		void Render()
		{
			gOTOXY(3, 17);
			std::cout << ANSI_COLOR_RESET "���� ȭ�� �׸���" << std::endl;
		}

		void Run()
		{
			Initialize();
			while (isGameRunning)
			{
				Update();
				Render();
			}
			Release();

		}

		void KeyEvent(char KeyInput)
		{
			switch (KeyInput)
			{
				//���� : �ѹ� ESC ������ �Ͻ� ������ �ǰ� ���⼭ �����⸦ �����ϸ� ������.
			case KEY_ESC:
				isGameRunning = false;
				break;
			case KEY_LEFT:
				gOTOXY(5, 5);
				std::cout << ANSI_COLOR_RED "���� ����  " << std::endl;
				break;
			case KEY_RIGHT:
				gOTOXY(5, 5);
				std::cout << ANSI_COLOR_GREEN "������ ����  " << std::endl;
				break;
			case KEY_ENTER:
				gOTOXY(5, 5);
				std::cout << ANSI_COLOR_BLUE "���� ����  " << std::endl;
				break;
			default:
				isGameRunning = true;
				break;
			}
		}
		//Ű�� �Է¹ޱ� ���ؼ� �ߴ��� ����Ѵ�.
			/*while (isGameRunning)
			{

				Update();

				std::cout << "���� ���� ��" << std::endl;
				if (_kbhit())
				{
					if (_getch() == 27)
					{
						isGameRunning = false;
					}
				}
			}*/
	};
}
//���� Windows ����Ÿ� ���� ��(F5�� ���� ��)
