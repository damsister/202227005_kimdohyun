//#include "game.h"
//#include <conio.h> // �ܼ� ��ǲ �ƿ�ǲ
//
//void Object::Render(char* screenBuf) const
//{
//    // Object�� ������ ��� ����
//    // screenBuf�� Ȱ���Ͽ� Object�� ����� �׸���.
//}
//
//Scene::Scene(int w, int h) : width(w), height(h)
//{
//    Initialize();
//}
//
//Scene::~Scene()
//{
//    ReleaseScreenBuf();
//}
//
//void Scene::Initialize()
//{
//    objList.clear();
//    InitScreenBuf();
//}
//
//void Scene::InitScreenBuf()
//{
//    screenBuf = new char[(width + 1) * height + height];
//    for (int i = 0; i < height; i++)
//    {
//        screenBuf[(width + 1) + (width + 1) * i - 1] = '\n';
//    }
//    screenBuf[(width + 1) + (width + 1) * (height - 1) - 1] = '\0';
//}
//
//void Scene::ReleaseScreenBuf()
//{
//    if (screenBuf != nullptr)
//    {
//        delete[] screenBuf;
//    }
//}
//
//void Scene::Draw()
//{
//    ClearScreenBuf();
//
//    // Active�� Object�� Render ȣ��
//    for (const Object& obj : objList)
//    {
//        obj.Render(screenBuf);
//    }
//
//    // ȭ�� ��ü�� ���
//    std::cout << screenBuf;
//}
//
//void Scene::ClearScreenBuf()
//{
//    for (int i = 0; i < (width + 1) * height; i++)
//    {
//        screenBuf[i] = ' ';
//    }
//}
//
//void Component::Start()
//{
//    // Start �Լ� ����
//}
//
//void Component::Update()
//{
//    // Update �Լ� ����
//}
//
//void print_title_screen()
//{
//    std::cout << "****************************************" << std::endl;
//    std::cout << "*                                      *" << std::endl;
//    std::cout << "*                                      *" << std::endl;
//    std::cout << "*             ������ ����              *" << std::endl;
//    std::cout << "*            (Snake Bite)              *" << std::endl;
//    std::cout << "*                                      *" << std::endl;
//    std::cout << "*            1. ���� ����              *" << std::endl;
//    std::cout << "*            2. ���� ����              *" << std::endl;
//    std::cout << "*            3. ���� ��ŷ ����         *" << std::endl;
//    std::cout << "*            4. ���� ���� (esc)        *" << std::endl;
//    std::cout << "*                                      *" << std::endl;
//    std::cout << "****************************************" << std::endl;
//}
//
//int introduction_screen()
//{
//	std::cout << ANSI_COLOR_RESET"******************************************" << std::endl;
//	std::cout << ANSI_COLOR_RESET"*         ���� ����ȭ���Դϴ�.           *" << std::endl;
//	std::cout << ANSI_COLOR_RESET"*         ���� ������ ���Ұ̴ϴ�.        *" << std::endl;
//	std::cout << ANSI_COLOR_RESET"******************************************" << std::endl;
//	std::cout << ANSI_COLOR_RESET"*   Ÿ��Ʋȭ������ ���ư����? (Y/N)     *" << std::endl;
//	std::cout << ANSI_COLOR_RESET"******************************************" << std::endl;
//	return 0;
//}
//
//void start_game()
//{
//    int width = 40;
//    int height = 20;
//
//    Scene scene(width, height);
//
//    for (int i = 0; i < height; i++)
//    {
//        for (int j = 0; j < width; j++)
//        {
//            if (i == height / 2 && j >= width / 2 - 1 && j <= width / 2 + 1)
//            {
//                std::cout << "@";
//            }
//            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
//            {
//                std::cout << "*";
//            }
//            else
//            {
//                std::cout << " ";
//            }
//        }
//        std::cout << std::endl;
//    }
//}
//
//
//int main()
//{
//	int game_state = 0; //���� ��������
//	int isgamerunning = 1; //���� ����
//	int mod_r = 1; //�ƹ� Ű�� �Է� ���� ���ϰ� �ϴ� �ڵ�
//	bool isYesSelected = true;
//
//	while (isgamerunning)
//	{
//		char key_input = 0;
//		switch (game_state)
//		{
//		case 0:
//			if (mod_r)
//			{
//				print_title_screen();
//				// scene�� screenBuf�� Ÿ��Ʋ ȭ�� ����
//			}
//
//			key_input = _getch();
//
//			mod_r = 0;
//
//			switch (key_input)
//			{
//			case '1':
//				game_state = 1;
//				mod_r = 1;
//				start_game();
//				break;
//			case '2':
//				game_state = 2;
//				mod_r = 1;
//				break;
//			case '3':
//				break;
//			case 27:
//				if (key_input == KEY_ESC)
//				{
//					isYesSelected = true;
//					mod_r = 0; //�ƹ� Ű�� �Է� ���� ���ϰ� �ϴ� �ڵ�
//					//���� ����
//					Gotoxy(5, 12);
//					std::cout << ANSI_COLOR_RESET "�����Ͻðڽ��ϱ�?" << std::endl;
//					Gotoxy(5, 13);
//					std::cout << ANSI_COLOR_YELLOW "[��]" << std::endl;
//					Gotoxy(15, 13);
//					std::cout << ANSI_COLOR_RESET "[�ƴϿ�]  " << std::endl;
//
//					while (true) // ESC�� ������ ���� ������ �ݺ��Ѵ�.
//					{
//						if (_kbhit()) //Ű �Է� �ޱ�
//						{
//							char key = _getch();
//
//							if (key == KEY_LEFT || key == KEY_RIGHT) // 'a' �Ǵ� 'd'�� �ԷµǸ� ���õ� �޴��� �����Ѵ�.
//							{
//								isYesSelected = !isYesSelected;
//
//								// ���õ� �޴��� ���� ����� �Ǵ� �⺻ �������� ����Ѵ�.
//								if (isYesSelected)
//								{
//									Gotoxy(5, 13);
//									std::cout << ANSI_COLOR_YELLOW "[��]  ";
//									Gotoxy(15, 13);
//									std::cout << ANSI_COLOR_RESET "[�ƴϿ�]  ";
//								}
//								else
//								{
//									Gotoxy(5, 13);
//									std::cout << ANSI_COLOR_RESET "[��]  ";
//									Gotoxy(15, 13);
//									std::cout << ANSI_COLOR_YELLOW "[�ƴϿ�]  ";
//								}
//							}
//							else if (key == KEY_ENTER) // Enter�� �ԷµǸ� ���õ� �޴��� ���� �����ϰų� ������ ��� �����Ѵ�.
//							{
//								if (isYesSelected)
//								{
//									isgamerunning = false;
//									break;
//								}
//								else
//								{
//									Gotoxy(5, 12);
//									std::cout << "                     " << std::endl; //���� �޽��� �����
//									Gotoxy(5, 13);
//									std::cout << "     " << std::endl; //���� �޴� �����
//									Gotoxy(15, 13);
//									std::cout << "        " << std::endl;
//									isgamerunning = true;
//									break; //�ݺ��� ����
//									print_title_screen();
//								}
//							}
//						}
//					}
//				}
//				break;
//			default:
//				break;
//			}
//			break;
//		case 1:
//			if (mod_r)
//			{
//				system("cls");
//				start_game();
//				//scene.objList.push_back(SnakeBody(scene.width / 2 - 1, scene.height / 2)); // �ʱ� ���� ��ġ�� �� ����� ����
//			}
//			key_input = _getch();
//			mod_r = 0;
//
//			switch (key_input)
//			{
//			case KEY_ESC:
//				game_state = 0;
//				mod_r = 1;
//				system("cls");
//				break;
//			case KEY_UP:
//				//snake.y++;
//				break;
//			case KEY_DOWN:
//				//snake.y--;
//				break;
//			default:
//				break;
//			}
//			break;
//		case 2:
//			if (mod_r)
//			{
//				system("cls");
//				introduction_screen();
//				// ���� ���� ȭ�� ����
//			}
//			key_input = 0;
//			key_input = _getch();
//
//			mod_r = 0;
//
//			if (key_input == 'y')
//			{
//				mod_r = 1;
//				game_state = 0;
//				system("cls");
//			}
//			else if (key_input == 'n')
//			{
//				isgamerunning = 0;
//			}
//
//		}
//	}
//	return 0;
//}
