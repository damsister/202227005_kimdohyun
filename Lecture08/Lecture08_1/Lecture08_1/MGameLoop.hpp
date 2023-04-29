#pragma once //라는 간단한 방법이 있음 
//#define _IS_THIS_HEADER_INCLUDED
#include <iostream>
#include <conio.h>
#include <Windows.h>

#define KEY_ESC 27 //아스키코드를 ESC로 정의
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_ENTER 13 

//색 코드(외울 필요 없음)
#define ANSI_COLOR_RED      "\x1b[31m" //바로 앞 문자열에 반영된다.
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
		//x, y 좌표 설정
		COORD pos = { x,y };
		//커서 이동
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	//커서 지우기
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
		MGameLoop() {} //생성자
		~MGameLoop() {} //소멸자

		bool isGameRunning = false;
		bool isMenuActive = false;
		bool isMenuYesSelected = true;

		void Initialize()
		{
			SetCursorState(false);
			GotoXY(3, 15);
			std::cout << ANSI_COLOR_RESET "게임 초기화 중" << std::endl;
			isGameRunning = true;
		}

		void Release()
		{
			GotoXY(3, 18);
			std::cout << ANSI_COLOR_RESET "게임 종료" << std::endl;
		}

		void Update()
		{
			if (isMenuActive)
			{
				// 메뉴 활성화 상태일 때
				if (_kbhit())
				{
					switch (_getch())
					{
					case KEY_LEFT:
					case KEY_RIGHT:
						// Yes와 No를 번갈아가면서 선택
						isMenuYesSelected = !isMenuYesSelected;
						break;
					case KEY_ENTER:
						// Enter 키를 누르면 메뉴 선택 완료
						isMenuActive = false;
						if (isMenuYesSelected)
						{
							isGameRunning = false;
						}
						break;
					}
				}

				// 메뉴 그리기
				GotoXY(10, 20);
				std::cout << (isMenuYesSelected ? ANSI_COLOR_YELLOW : ANSI_COLOR_RESET) << "[예]  ";
				GotoXY(20, 20);
				std::cout << (!isMenuYesSelected ? ANSI_COLOR_YELLOW : ANSI_COLOR_RESET) << "[아니오]  ";
				return;
			}

			GotoXY(3, 16);
			std::cout << ANSI_COLOR_RESET "게임 키입력 대기" << std::endl;
			
			if (_kbhit())
			{
				KeyEvent(_getch()); //이 함수를 받아서
			}
				
		}

		void Render()
		{
			GotoXY(3, 17);
			std::cout << ANSI_COLOR_RESET "게임 화면 그리기" << std::endl;
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
				//과제 : 한번 ESC 누르면 일시 정지가 되고 여기서 나가기를 선택하면 나간다.
			case KEY_ESC:
				GotoXY(5, 21);
				std::cout << ANSI_COLOR_RESET "종료하시겠습니까?" << std::endl;
				GotoXY(5, 23);
				std::cout << ANSI_COLOR_YELLOW "[예]" << std::endl;
				GotoXY(17, 23);
				std::cout << ANSI_COLOR_RESET "[아니오]  " << std::endl;
				GotoXY(5, 23); //처음 선택된 메뉴는 "예"

				while (true) // ESC를 눌러서 나갈 때까지 반복한다.
				{
					if (_kbhit()) //키 입력 받기
					{
						char key = _getch();

						if (key == KEY_LEFT || key == KEY_RIGHT) // 'a' 또는 'd'가 입력되면 선택된 메뉴를 변경한다.
						{
							isYesSelected = !isYesSelected;

							// 선택된 메뉴에 따라 노란색 또는 기본 색상으로 출력한다.
							if (isYesSelected)
							{
								GotoXY(5, 23);
								std::cout << ANSI_COLOR_YELLOW "[예]  " << std::endl;
								GotoXY(17, 23);
								std::cout << ANSI_COLOR_RESET "[아니오]  " << std::endl;
							}
							else
							{
								GotoXY(5, 23);
								std::cout << ANSI_COLOR_RESET "[예]  " << std::endl;
								GotoXY(17, 23);
								std::cout << ANSI_COLOR_YELLOW "[아니오]  " << std::endl;
							}
						}
						else if (key == KEY_ENTER) // Enter가 입력되면 선택된 메뉴에 따라 종료하거나 게임을 계속 실행한다.
						{
							if (isYesSelected)
							{
								isGameRunning = false;
								break;
							}
							else
							{
								GotoXY(3, 21);
								std::cout << "                     " << std::endl; //종료 메시지 지우기
								GotoXY(5, 23);
								std::cout << "     " << std::endl; //선택 메뉴 지우기
								GotoXY(17, 23);
								std::cout << "        " << std::endl;
								isGameRunning = true;
								break; //반복문 종료
							}
						}
					}
				}
			break;
			case KEY_LEFT:
				GotoXY(5, 5);
				std::cout << ANSI_COLOR_RED "왼쪽 눌림  " << std::endl;
				break;
			case KEY_RIGHT:
				GotoXY(5, 5);
				std::cout << ANSI_COLOR_GREEN "오른쪽 눌림  " << std::endl;
				break;
			case KEY_ENTER:
				GotoXY(5, 5);
				std::cout << ANSI_COLOR_BLUE "엔터 눌림  " << std::endl;
				break;
			default:
				isGameRunning = true;
				break;
			}
		}
		//키를 입력받기 위해서 중단점 사용한다.
			/*while (isGameRunning)
			{

				Update();

				std::cout << "게임 실행 중" << std::endl;
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
//로컬 Windows 디버거를 누를 것(F5를 누를 것)
