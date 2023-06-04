#include "game.h"
#include <iostream>
#include <conio.h>// �ܼ� ��ǲ �ƿ�ǲ
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
    // ���� �ε����� �� ���� ����
    if (x <= 0 || x >= scene.width - 2 || y <= 0 || y >= scene.height - 1) {
        isAlive = false;
    }

    // ������ �ε����� �� ���� ����
    for (int i = 1; i < tail.size(); i++) {
        if (x == tail[i].x && y == tail[i].y) {
            isAlive = false;
            break;
        }
    }
}

void Object::Render(char* screenBuf) const
{
    // Object�� ������ ��� ����
    // screenBuf�� Ȱ���Ͽ� Object�� ����� �׸���.
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

    // Active�� Object�� Render ȣ��
    for (const Object& obj : objList)
    {
        obj.Render(screenBuf);
    }

    // ȭ�� ��ü�� ���
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
//    // Start �Լ� ����
//}
//
//void Component::Update()
//{
//    // Update �Լ� ����
//}

void print_title_screen()
{
    std::cout << "****************************************" << std::endl;
    std::cout << "*                                      *" << std::endl;
    std::cout << "*                                      *" << std::endl;
    std::cout << "*          �챺�� �� ��������          *" << std::endl;
    std::cout << "*                                      *" << std::endl;
    std::cout << "*            1. ���� ����              *" << std::endl;
    std::cout << "*            2. ���� ����              *" << std::endl;
    std::cout << "*           ���� ���� (esc)            *" << std::endl;
    std::cout << "*                                      *" << std::endl;
    std::cout << "****************************************" << std::endl;
}

int introduction_screen()
{
    std::cout << ANSI_COLOR_RESET"******************************************" << std::endl;
    std::cout << ANSI_COLOR_RESET"*         ���� ����ȭ���Դϴ�.           *" << std::endl;
    std::cout << ANSI_COLOR_RESET"*         ���� ������ ���Ұ̴ϴ�.        *" << std::endl;
    std::cout << ANSI_COLOR_RESET"******************************************" << std::endl;
    std::cout << ANSI_COLOR_RESET"*   Ÿ��Ʋȭ������ ���ư����? (Y/N)     *" << std::endl;
    std::cout << ANSI_COLOR_RESET"******************************************" << std::endl;
    return 0;
}

int GameOver_screen()
{
    Gotoxy(5, 10);
    std::cout << "*************************" << std::endl;
    std::cout << "*       ���� ����       *" << std::endl;
    std::cout << "*************************" << std::endl;
    return 0;
}

void start_game()
{
    int width = 40;
    int height = 20;

    Scene scene(width, height);

    // �� ����
    Snake snake(scene.width / 2 - 1, scene.height / 2);

    while (true)
    {
        if (_kbhit()) // Ű �Է� �ޱ�
        {
            char key = _getch();

            switch (key)
            {
            case KEY_LEFT:
                snake.direction = LEFT; // ���� ������ �������� ����
                break;
            case KEY_RIGHT:
                snake.direction = RIGHT; // ���� ������ ���������� ����
                break;
            case KEY_UP:
                snake.direction = UP; // ���� ������ ���� ����
                break;
            case KEY_DOWN:
                snake.direction = DOWN; // ���� ������ �Ʒ��� ����
                break;
            }

            // �� �̵� ��, ���ο� ��ġ�� �� �׸���
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (i == snake.y && j >= snake.x && j <= snake.x + 1)
                    {
                        std::cout << ANSI_COLOR_BLUE "@"; // �̵��� �� ǥ��
                    }
                    else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                    {
                        std::cout << ANSI_COLOR_RESET "*"; // �� ǥ��
                    }
                    else
                    {
                        std::cout << ANSI_COLOR_RESET " "; // �� ���� ǥ��
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
            // Ű �Է��� ���� ������ ����ؼ� ���� �̵���ŵ�ϴ�.
            switch (snake.direction)
            {
            case LEFT:
                snake.MoveLeft(); // ���� �������� �̵�
                break;
            case RIGHT:
                snake.MoveRight(); // ���� ���������� �̵�
                break;
            case UP:
                snake.MoveUp(); // ���� ���� �̵�
                break;
            case DOWN:
                snake.MoveDown(); // ���� �Ʒ��� �̵�
                break;
            }

            // �� �̵� ��, ���ο� ��ġ�� �� �׸���
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (i == snake.y && j >= snake.x && j <= snake.x + 1)
                    {
                        std::cout << ANSI_COLOR_BLUE "@"; // �̵��� �� ǥ��
                    }
                    else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                    {
                        std::cout << ANSI_COLOR_RESET "*"; // �� ǥ��
                    }
                    else
                    {
                        std::cout << ANSI_COLOR_RESET " "; // �� ���� ǥ��
                    }
                }
                std::cout << std::endl;
            }
            system("cls");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // �� �̵� ������
        // ���� ���� ó��
        if (!snake.isAlive) {
            GameOver_screen();
            break;
        }
    }
}

int main()
{
    int game_state = 0; // ���� ��������
    int isgamerunning = 1; // ���� ����
    int mod_r = 1; // �ƹ� Ű�� �Է� ���� ���ϰ� �ϴ� �ڵ�
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
                // scene�� screenBuf�� Ÿ��Ʋ ȭ�� ����
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
                    mod_r = 0; // �ƹ� Ű�� �Է� ���� ���ϰ� �ϴ� �ڵ�
                    // ���� ����
                    Gotoxy(5, 12);
                    std::cout << ANSI_COLOR_RESET "�����Ͻðڽ��ϱ�?" << std::endl;
                    Gotoxy(5, 13);
                    std::cout << ANSI_COLOR_YELLOW "[��]" << std::endl;
                    Gotoxy(15, 13);
                    std::cout << ANSI_COLOR_RESET "[�ƴϿ�]  " << std::endl;

                    while (true) // ESC�� ������ ���� ������ �ݺ��Ѵ�.
                    {
                        if (_kbhit()) // Ű �Է� �ޱ�
                        {
                            char key = _getch();

                            if (key == KEY_LEFT || key == KEY_RIGHT) // 'a' �Ǵ� 'd'�� �ԷµǸ� ���õ� �޴��� �����Ѵ�.
                            {
                                isYesSelected = !isYesSelected;

                                // ���õ� �޴��� ���� ����� �Ǵ� �⺻ �������� ����Ѵ�.
                                if (isYesSelected)
                                {
                                    Gotoxy(5, 13);
                                    std::cout << ANSI_COLOR_YELLOW "[��]  ";
                                    Gotoxy(15, 13);
                                    std::cout << ANSI_COLOR_RESET "[�ƴϿ�]  ";
                                }
                                else
                                {
                                    Gotoxy(5, 13);
                                    std::cout << ANSI_COLOR_RESET "[��]  ";
                                    Gotoxy(15, 13);
                                    std::cout << ANSI_COLOR_YELLOW "[�ƴϿ�]  ";
                                }
                            }
                            else if (key == KEY_ENTER) // Enter�� �ԷµǸ� ���õ� �޴��� ���� �����ϰų� ������ ��� �����Ѵ�.
                            {
                                if (isYesSelected)
                                {
                                    isgamerunning = false;
                                    break;
                                }
                                else
                                {
                                    Gotoxy(5, 12);
                                    std::cout << "                     " << std::endl; // ���� �޽��� �����
                                    Gotoxy(5, 13);
                                    std::cout << "     " << std::endl; // ���� �޴� �����
                                    Gotoxy(15, 13);
                                    std::cout << "        " << std::endl;
                                    isgamerunning = true;
                                    break; // �ݺ��� ����
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
//chrono:��ǻ�� �ý��� �ð�
//startRenderTiemPoint = chrono::system_clock::now(); //����ð��������� 
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

//kbhit()//ȭ���� ���ų� �� �Է��� ���� ����
//���������� 1 -> �Է�
//���������� 0 -> �Է�X
//������ : ���ÿ� ����