#define _CRT_SECURE_NO_WARNINGS
#include <iostream> //input output 스트림
#include <conio.h> //콘솔 인풋 아웃풋
#include <Windows.h>  // gotoxy

char** map = NULL;

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

//int InitMap()
//{
//	if (map == nullptr)
//	{
//		map = (char**)malloc(sizeof(char*) * stage_);
//		for (int i = 0; i < stage_height; i++)
//		{
//			map[i] = new char[stage_width];
//		}
//	}
//	return 0;
//}

int ReleaseMap()
{

}

int print_game_screen(int stage_width, int stage_height)
{
	for (int i = 0; i < stage_width + 2; i++)
	{
		gotoxy(i, 0); //가로
		std::cout << "●" << std::endl;

		gotoxy(i, stage_height + 1); //1칸 이동해서 세로 그리기
		std::cout << "●" << std::endl;
	}
	for (int i = 0; i < stage_height + 2; i++)
	{
		gotoxy(0, i); //(0,0)으로 이동해서 세로 그림
		std::cout << "●" << std::endl;

		gotoxy(stage_width + 1, i); //1칸 이동해서 가로 그리기
		std::cout << "●" << std::endl;
	}

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
	/*int game_state = 0; //게임 스테이지를 나타낼 변수
	int is_game_runing = 1; //게임 종료(1:참, 0:거짓)
	int mod_r = 1; //무조건 타이틀 화면이 나타나게 해야함
	// 아무 키를 눌렀을 때 타이틀 화면이 나타나지 않게 하는 변수

	while (is_game_runing)
	{
		char key_input = 0; //key_input 초기화
		switch (game_state) //전체 타이틀
		{
		case 0:
			if (mod_r) //1일 경우
			{
				print_title_screen();
			}

			key_input = _getch(); //1~4 중 입력을 받음

			mod_r = 0; //0으로 만들어서 해당 화면이 뜰 수 있게 만듬

			switch (key_input)
			{
			case '1':
				game_state = 1;
				mod_r = 1; //아무 키로 입력받지 않게 막음
				break; //while문으로 이동
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
				scanf("%d", &y);
				system("cls"); //출력된 화면을 지워주는 코드
				print_game_screen(x, y);
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

	}*/

	//game_state 
//0 : 게임 종료
//1 : 시작 화면
//2 : 게임 설명
//3 : 랭킹 화면

	int game_state = 1;

	while (game_state)
	{
		switch (game_state)
		{
		case 0:
			game_state = 0;
			break;
		case 1:
			print_title_screen();
			int sub_title_state = 1;
			while (sub_title_state) //0이 되면 종료
			{
				char key_input = _getch();
				switch (key_input)
				{
				case 0:
					game_state = 0; //게임 종료
					break;
				case 1:
					game_state = 1;
					break;
				case 2:
					game_state = 2;
					break;
				case 3:
					game_state = 3;
					break;
				default:
					break;
				}
			}
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
	}
	return 0;
}