#define _CRT_SECURE_NO_WARNINGS
#include <iostream> //input output 스트림
#include <conio.h> //콘솔 인풋 아웃풋
#include <Windows.h>  // gotoxy

char** map = NULL;
int stage_width = 15;
int stage_height = 15;
//game state == 0
int print_title_screen()
{
	std::cout << "******************************************" << std::endl;
	std::cout << "*                                        *" << std::endl;
	std::cout << "*                                        *" << std::endl;
	std::cout << "*              지렁이 게임               *" << std::endl;
	std::cout << "*             (Snake  Bite)              *" << std::endl;
	std::cout << "*                                        *" << std::endl;
	std::cout << "*   1. 게임 시작                         *" << std::endl;
	std::cout << "*   2. 게임 설명                         *" << std::endl;
	std::cout << "*   3. 게임 랭킹 보기                    *" << std::endl;
	std::cout << "*   4. 게임 종료 (esc)                   *" << std::endl;
	std::cout << "******************************************" << std::endl;

	return 0;
}

void gotoxy(int x, int y) {
	//x, y 좌표 설정
	COORD pos = { x * 2,y };//가로의 간격이 조금 짧아서 간격을 띄워주기 위해 *2를 해줘야함
	//커서 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//Window.h에 포함되어 있음
}

int InitMap()//뱀을 생성하지 못했습니다.ㅠㅠ
{
	//// 뱀 생성
	//int snake_x = 3;
	//int snake_y = 1;
	//map[snake_y][snake_x] = '@';
	//map[snake_y][snake_x + 1] = '#';
	//map[snake_y][snake_x + 2] = '#';
	return 0;
}

int print_game_screen(int stage_width, int stage_height)
{
	//맵 생성
	char** map = (char**)malloc(sizeof(char*) * stage_height);
	for (int i = 0; i < stage_height; i++)
	{
		map[i] = (char*)malloc(sizeof(char) * stage_width);
		// 맵 초기화
		for (int j = 0; j < stage_width; j++)
		{
			if (i == 0 || i == stage_height - 1 || j == 0 || j == stage_width - 1)
			{
				// 가장자리는 벽으로 만듦
				map[i][j] = '*';
			}
			else
			{
				// 그 외는 빈 공간으로 만듦
				map[i][j] = ' ';
			}
		}
	}

	// 맵 출력
	for (int i = 0; i < stage_height; i++)
	{
		for (int j = 0; j < stage_width; j++)
		{
			std::cout << map[i][j] << " ";
		}
		std::cout << std::endl;
	}

	// 메모리 해제
	for (int i = 0; i < stage_height; i++)
	{
		free(map[i]);
	}
	free(map);

	return 0;
}

// game_state == 2 일때
int print_introduction_screen()
{
	std::cout << "******************************************" << std::endl;
	std::cout << "*         게임 설명화면입니다.           *" << std::endl;
	std::cout << "*         게임 설명은 안할겁니다.        *" << std::endl;
	std::cout << "******************************************" << std::endl;
	std::cout << "*   타이틀화면으로 돌아갈까요? (Y/N)     *" << std::endl;
	std::cout << "******************************************" << std::endl;
	return 0;
}

int main()
{
	int game_state = 0; //게임 스테이지
	int is_game_runing = 1; //게임 종료
	int mod_r = 1; //아무 키를 입력 받지 못하게 하는 코드

	while (is_game_runing)
	{
		char key_input = 0;
		switch (game_state)
		{
		case 0:
			if (mod_r)
			{
				print_title_screen();
			}

			key_input = _getch();

			mod_r = 0;

			switch (key_input)
			{
			case '1':
				game_state = 1;
				mod_r = 1;
				break;
			case '2':
				game_state = 2;
				mod_r = 1;
				break;
			case '3':
				break;
			case '4':
				is_game_runing = 0;
				break;
			case 27:
				is_game_runing = 0;
				break;
			default:
				break;
			}
			break;
		case 1:
			if (mod_r)
			{
				int x = 0;
				int y = 0;
				std::cout << "너비와 높이를 입력하세요: " << std::endl;
				scanf("%d", &x);
				x = x + 2;
				scanf("%d", &y);
				y = y + 2;
				system("cls");
				print_game_screen(x, y);
				InitMap();
			};
			key_input = _getch();
			mod_r = 0;
			break;
		case 2:
			if (mod_r)
			{
				print_introduction_screen();
			}

			key_input = 0;
			key_input = _getch();

			mod_r = 0;

			if (key_input == 'y')
			{
				mod_r = 1;
				game_state = 0;
			}
			else if (key_input == 'n')
			{

			}

		default:
			break;
		}

	}
	return 0;
}