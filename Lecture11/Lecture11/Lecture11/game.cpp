#include "game.h"
#include <iostream>
#include <conio.h>// 콘솔 인풋 아웃풋
#include <thread>
#include <chrono>

bool isGameOver = false;

Snake::Snake(int startX, int startY)
{
    x = startX;
    y = startY;
    direction;
    isAlive = true;
}

void Snake::MoveLeft() {
    x--;
    CheckCollision();
}

void Snake::MoveRight() {
    x++;
    CheckCollision();
}

void Snake::MoveUp() {
    y--;
    CheckCollision();
}

void Snake::MoveDown() {
    y++;
    CheckCollision();
}

void Snake::CheckCollision() {
    // 벽에 부딪혔을 때 게임 오버
    if (x <= 0 || x >= scene.width - 2 || y <= 0 || y >= scene.height - 1) {
        isAlive = false;
    }

    // 꼬리에 부딪혔을 때 게임 오버
    for (int i = 1; i < tail.size(); i++) {
        if (x == tail[i].x && y == tail[i].y) {
            isAlive = false;
            break;
        }
    }
}

void Object::Render(char* screenBuf) const
{
    // Object의 렌더링 기능 구현
    // screenBuf를 활용하여 Object의 모양을 그린다.
}

Scene::Scene(int w, int h) : width(w), height(h)
{
    Initialize();
}

Scene::~Scene()
{
    ReleaseScreenBuf();
}

void Scene::Initialize()
{
    objList.clear();
    InitScreenBuf();
}

void Scene::InitScreenBuf()
{
    screenBuf = new char[(width + 1) * height + height];
    for (int i = 0; i < height; i++)
    {
        screenBuf[(width + 1) + (width + 1) * i - 1] = '\n';
    }
    screenBuf[(width + 1) + (width + 1) * (height - 1) - 1] = '\0';
}

void Scene::ReleaseScreenBuf()
{
    if (screenBuf != nullptr)
    {
        delete[] screenBuf;
    }
}

void Scene::Draw()
{
    ClearScreenBuf();

    // Active한 Object의 Render 호출
    for (const Object& obj : objList)
    {
        obj.Render(screenBuf);
    }

    // 화면 전체를 출력
    std::cout << screenBuf;
}

void Scene::ClearScreenBuf()
{
    for (int i = 0; i < (width + 1) * height; i++)
    {
        screenBuf[i] = ' ';
    }
}

//void Component::Start()
//{
//    // Start 함수 구현
//}
//
//void Component::Update()
//{
//    // Update 함수 구현
//}

void print_title_screen()
{
    std::cout << "****************************************" << std::endl;
    std::cout << "*                                      *" << std::endl;
    std::cout << "*                                      *" << std::endl;
    std::cout << "*          뱀군아 공 가져가라          *" << std::endl;
    std::cout << "*                                      *" << std::endl;
    std::cout << "*            1. 게임 시작              *" << std::endl;
    std::cout << "*            2. 게임 설명              *" << std::endl;
    std::cout << "*           게임 종료 (esc)            *" << std::endl;
    std::cout << "*                                      *" << std::endl;
    std::cout << "****************************************" << std::endl;
}

int introduction_screen()
{
    std::cout << ANSI_COLOR_RESET"******************************************" << std::endl;
    std::cout << ANSI_COLOR_RESET"*         게임 설명화면입니다.           *" << std::endl;
    std::cout << ANSI_COLOR_RESET"*         게임 설명은 안할겁니다.        *" << std::endl;
    std::cout << ANSI_COLOR_RESET"******************************************" << std::endl;
    std::cout << ANSI_COLOR_RESET"*   타이틀화면으로 돌아갈까요? (Y/N)     *" << std::endl;
    std::cout << ANSI_COLOR_RESET"******************************************" << std::endl;
    return 0;
}

int GameOver_screen()
{
    Gotoxy(5, 10);
    std::cout << "*************************" << std::endl;
    std::cout << "*       게임 오버       *" << std::endl;
    std::cout << "*************************" << std::endl;
    return 0;
}

void start_game()
{
    int width = 40;
    int height = 20;

    Scene scene(width, height);

    // 뱀 생성
    Snake snake(scene.width / 2 - 1, scene.height / 2);

    while (true)
    {
        if (_kbhit()) // 키 입력 받기
        {
            char key = _getch();

            switch (key)
            {
            case KEY_LEFT:
                snake.direction = LEFT; // 뱀의 방향을 왼쪽으로 설정
                break;
            case KEY_RIGHT:
                snake.direction = RIGHT; // 뱀의 방향을 오른쪽으로 설정
                break;
            case KEY_UP:
                snake.direction = UP; // 뱀의 방향을 위로 설정
                break;
            case KEY_DOWN:
                snake.direction = DOWN; // 뱀의 방향을 아래로 설정
                break;
            }

            // 뱀 이동 후, 새로운 위치에 뱀 그리기
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (i == snake.y && j >= snake.x && j <= snake.x + 1)
                    {
                        std::cout << ANSI_COLOR_BLUE "@"; // 이동한 뱀 표시
                    }
                    else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                    {
                        std::cout << ANSI_COLOR_RESET "*"; // 벽 표시
                    }
                    else
                    {
                        std::cout << ANSI_COLOR_RESET " "; // 빈 공간 표시
                    }
                }
                std::cout << std::endl;
            }
            if (key == KEY_ESC)
            {
                break;
                system("cls");
                print_title_screen();
            }
        }
        else
        {
            // 키 입력이 없을 때에는 계속해서 뱀을 이동시킵니다.
            switch (snake.direction)
            {
            case LEFT:
                snake.MoveLeft(); // 뱀을 왼쪽으로 이동
                break;
            case RIGHT:
                snake.MoveRight(); // 뱀을 오른쪽으로 이동
                break;
            case UP:
                snake.MoveUp(); // 뱀을 위로 이동
                break;
            case DOWN:
                snake.MoveDown(); // 뱀을 아래로 이동
                break;
            }

            // 뱀 이동 후, 새로운 위치에 뱀 그리기
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (i == snake.y && j >= snake.x && j <= snake.x + 1)
                    {
                        std::cout << ANSI_COLOR_BLUE "@"; // 이동한 뱀 표시
                    }
                    else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                    {
                        std::cout << ANSI_COLOR_RESET "*"; // 벽 표시
                    }
                    else
                    {
                        std::cout << ANSI_COLOR_RESET " "; // 빈 공간 표시
                    }
                }
                std::cout << std::endl;
            }
            system("cls");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // 뱀 이동 딜레이
        // 게임 오버 처리
        if (!snake.isAlive) {
            GameOver_screen();
            break;
        }
    }
}

int main()
{
    int game_state = 0; // 게임 스테이지
    int isgamerunning = 1; // 게임 종료
    int mod_r = 1; // 아무 키를 입력 받지 못하게 하는 코드
    bool isYesSelected = true;

    while (isgamerunning)
    {
        char key_input = 0;
        switch (game_state)
        {
        case 0:
            if (mod_r)
            {
                print_title_screen();
                // scene의 screenBuf에 타이틀 화면 저장
            }

            key_input = _getch();

            mod_r = 0;

            switch (key_input)
            {
            case '1':
                game_state = 1;
                mod_r = 1;
                system("cls");
                start_game();
                break;
            case '2':
                game_state = 2;
                mod_r = 1;
                break;
            case 27:
                if (key_input == KEY_ESC)
                {
                    isYesSelected = true;
                    mod_r = 0; // 아무 키를 입력 받지 못하게 하는 코드
                    // 게임 종료
                    Gotoxy(5, 12);
                    std::cout << ANSI_COLOR_RESET "종료하시겠습니까?" << std::endl;
                    Gotoxy(5, 13);
                    std::cout << ANSI_COLOR_YELLOW "[예]" << std::endl;
                    Gotoxy(15, 13);
                    std::cout << ANSI_COLOR_RESET "[아니오]  " << std::endl;

                    while (true) // ESC를 눌러서 나갈 때까지 반복한다.
                    {
                        if (_kbhit()) // 키 입력 받기
                        {
                            char key = _getch();

                            if (key == KEY_LEFT || key == KEY_RIGHT) // 'a' 또는 'd'가 입력되면 선택된 메뉴를 변경한다.
                            {
                                isYesSelected = !isYesSelected;

                                // 선택된 메뉴에 따라 노란색 또는 기본 색상으로 출력한다.
                                if (isYesSelected)
                                {
                                    Gotoxy(5, 13);
                                    std::cout << ANSI_COLOR_YELLOW "[예]  ";
                                    Gotoxy(15, 13);
                                    std::cout << ANSI_COLOR_RESET "[아니오]  ";
                                }
                                else
                                {
                                    Gotoxy(5, 13);
                                    std::cout << ANSI_COLOR_RESET "[예]  ";
                                    Gotoxy(15, 13);
                                    std::cout << ANSI_COLOR_YELLOW "[아니오]  ";
                                }
                            }
                            else if (key == KEY_ENTER) // Enter가 입력되면 선택된 메뉴에 따라 종료하거나 게임을 계속 실행한다.
                            {
                                if (isYesSelected)
                                {
                                    isgamerunning = false;
                                    break;
                                }
                                else
                                {
                                    Gotoxy(5, 12);
                                    std::cout << "                     " << std::endl; // 종료 메시지 지우기
                                    Gotoxy(5, 13);
                                    std::cout << "     " << std::endl; // 선택 메뉴 지우기
                                    Gotoxy(15, 13);
                                    std::cout << "        " << std::endl;
                                    isgamerunning = true;
                                    break; // 반복문 종료
                                    print_title_screen();
                                }
                            }
                        }
                    }
                }
                break;
            default:
                break;
            }
            break;
        case 1:
            if (mod_r)
            {
                system("cls");
                start_game();
            }
            key_input = _getch();
            mod_r = 0;

            switch (key_input)
            {
            case KEY_ESC:
                game_state = 0;
                mod_r = 1;
                system("cls");
                break;
            default:
                break;
            }
            break;
        case 2:
            if (mod_r)
            {
                system("cls");
                introduction_screen();
            }
            key_input = _getch();
            mod_r = 0;

            if (key_input == 'y')
            {
                mod_r = 1;
                game_state = 0;
                system("cls");
            }
            else if (key_input == 'n')
            {
                isgamerunning = 0;
            }
            break;
        }
    }

    return 0;
}

//#include <chrono>
//chrono:컴퓨터 시스템 시간
//startRenderTiemPoint = chrono::system_clock::now(); //현재시간가져오는 
//isKeyPressed();

//class Scene
// vector<object>
// sc[000]
//class Object
// vector<commpont>
//class Commpont
//start()
//update()

//transform
//rigidbody : Commpont
// new() -> vector<commpont> push-> cubeobj new()-> vector<object> Scene.Draw->vector<commpont>
//

//kbhit()//화면을 띄우거나 등 입력을 받지 않음
//눌려있으면 1 -> 입력
//떼져있으면 0 -> 입력X
//스레드 : 동시에 시작