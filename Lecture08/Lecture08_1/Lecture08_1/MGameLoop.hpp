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
	void GotoXY(int x, int y) 
	{
		//x, y ��ǥ ����
		COORD pos = { x,y };
		//Ŀ�� �̵�
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	//Ŀ�� �����
	void SetCursorState(bool visible)
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
		bool isMenuActive = false;
		bool isMenuYesSelected = true;

		void Initialize()
		{
			SetCursorState(false);
			GotoXY(3, 15);
			std::cout << ANSI_COLOR_RESET "���� �ʱ�ȭ ��" << std::endl;
			isGameRunning = true;
		}

		void Release()
		{
			GotoXY(3, 18);
			std::cout << ANSI_COLOR_RESET "���� ����" << std::endl;
		}

		void Update()
		{
			if (isMenuActive)
			{
				// �޴� Ȱ��ȭ ������ ��
				if (_kbhit())
				{
					switch (_getch())
					{
					case KEY_LEFT:
					case KEY_RIGHT:
						// Yes�� No�� �����ư��鼭 ����
						isMenuYesSelected = !isMenuYesSelected;
						break;
					case KEY_ENTER:
						// Enter Ű�� ������ �޴� ���� �Ϸ�
						isMenuActive = false;
						if (isMenuYesSelected)
						{
							isGameRunning = false;
						}
						break;
					}
				}

				// �޴� �׸���
				GotoXY(10, 20);
				std::cout << (isMenuYesSelected ? ANSI_COLOR_YELLOW : ANSI_COLOR_RESET) << "[��]  ";
				GotoXY(20, 20);
				std::cout << (!isMenuYesSelected ? ANSI_COLOR_YELLOW : ANSI_COLOR_RESET) << "[�ƴϿ�]  ";
				return;
			}

			GotoXY(3, 16);
			std::cout << ANSI_COLOR_RESET "���� Ű�Է� ���" << std::endl;
			
			if (_kbhit())
			{
				KeyEvent(_getch()); //�� �Լ��� �޾Ƽ�
			}
				
		}

		void Render()
		{
			GotoXY(3, 17);
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
			bool isYesSelected = true;
			switch (KeyInput)
			{
				//���� : �ѹ� ESC ������ �Ͻ� ������ �ǰ� ���⼭ �����⸦ �����ϸ� ������.
			case KEY_ESC:
				GotoXY(5, 21);
				std::cout << ANSI_COLOR_RESET "�����Ͻðڽ��ϱ�?" << std::endl;
				GotoXY(5, 23);
				std::cout << ANSI_COLOR_YELLOW "[��]" << std::endl;
				GotoXY(17, 23);
				std::cout << ANSI_COLOR_RESET "[�ƴϿ�]  " << std::endl;
				GotoXY(5, 23); //ó�� ���õ� �޴��� "��"

				while (true) // ESC�� ������ ���� ������ �ݺ��Ѵ�.
				{
					if (_kbhit()) //Ű �Է� �ޱ�
					{
						char key = _getch();

						if (key == KEY_LEFT || key == KEY_RIGHT) // 'a' �Ǵ� 'd'�� �ԷµǸ� ���õ� �޴��� �����Ѵ�.
						{
							isYesSelected = !isYesSelected;

							// ���õ� �޴��� ���� ����� �Ǵ� �⺻ �������� ����Ѵ�.
							if (isYesSelected)
							{
								GotoXY(5, 23);
								std::cout << ANSI_COLOR_YELLOW "[��]  " << std::endl;
								GotoXY(17, 23);
								std::cout << ANSI_COLOR_RESET "[�ƴϿ�]  " << std::endl;
							}
							else
							{
								GotoXY(5, 23);
								std::cout << ANSI_COLOR_RESET "[��]  " << std::endl;
								GotoXY(17, 23);
								std::cout << ANSI_COLOR_YELLOW "[�ƴϿ�]  " << std::endl;
							}
						}
						else if (key == KEY_ENTER) // Enter�� �ԷµǸ� ���õ� �޴��� ���� �����ϰų� ������ ��� �����Ѵ�.
						{
							if (isYesSelected)
							{
								isGameRunning = false;
								break;
							}
							else
							{
								GotoXY(3, 21);
								std::cout << "                     " << std::endl; //���� �޽��� �����
								GotoXY(5, 23);
								std::cout << "     " << std::endl; //���� �޴� �����
								GotoXY(17, 23);
								std::cout << "        " << std::endl;
								isGameRunning = true;
								break; //�ݺ��� ����
							}
						}
					}
				}
			break;
			case KEY_LEFT:
				GotoXY(5, 5);
				std::cout << ANSI_COLOR_RED "���� ����  " << std::endl;
				break;
			case KEY_RIGHT:
				GotoXY(5, 5);
				std::cout << ANSI_COLOR_GREEN "������ ����  " << std::endl;
				break;
			case KEY_ENTER:
				GotoXY(5, 5);
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
