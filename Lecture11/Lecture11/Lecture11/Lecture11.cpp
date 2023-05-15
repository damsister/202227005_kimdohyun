// Lecture11.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

#include <iostream>

//과제: 그동안 만들었던 3가지를 이곳에 만들기
namespace MuSoeun
{
    class Scene
    {
        //뷰포트의 width, height가 저장되어있어야함
    public:
        int width;
        int height;
        std::vector<Object> objList; //벡터
        //screenBuf[width+(width*height);
        char* screenBuf;
        void InitScreenBuf()
        {
            screenBuf = new char[(width + 1) * height + 5];
            for (int i; i < height; i++) //맵 테두리 만드는 코드
            {

            }
        }
    };
    //Scene안에 char* screenBuf;를 넣어서
    //std::cout << screenBuf;로 한 번에 출력
    //new로 만든 것은 무조건 해제해라 -> 안하면 메모리 누수 발생
    
    class Object
    {
        void Rander();
        //버퍼에 그린다.
    };

    class Component //:Monobehavior
    {
        void Start(); //SetActive가 나왔을 때 한 번만 실행
        void Update(); //SetActive가 나왔을 때 매번 실행
        //SetActive는 오브젝트에서 설정
    };
}
int main()
{
    while (1)
    {

    }
    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
