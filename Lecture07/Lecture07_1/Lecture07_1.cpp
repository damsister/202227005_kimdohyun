// std : 네임스페이스

#include <iostream>
//private는 혼자 개발할 때는 잘 사용하지 않음
//협력할 때는 가끔 사용함
//그래도 public으로 사용하기

using namespace std;

class Animal
{
public:
    Animal()
    {
        cout << "Animal : 동물이다잉 (탄생)" << endl;
    }
    virtual ~Animal()
    {
        cout << "Animal : 죽었어 (죽음)" << endl;
    }
    virtual void Talk()
    {
        cout << "Animal : 동물이 뭔 말을 해" << endl;
    }
};

class Hamster : public Animal
{
public:
    Hamster()
    {
        cout << "Hamster : 찍(탄생)" << endl;
    }
    ~Hamster()
    {
        cout << "Hamster : 히이이익(죽음)" << endl;
    }

    void Talk()
    {
        cout << "Hamster : 뀨~" << endl;
    }
};

class Cat : public Animal
{
public:
    Cat()
    {
        cout << "Cat : 니야아아아옹(탄생)" << endl; //생성자
    }
    ~Cat()
    {
        cout << "Cat : 끄앙!(죽음)" << endl; //생성자 만들면 소멸자 꼭 만들기
    }

    /*void Meow()
    {
        cout << "Cat : 야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹!" << endl;
    }*/
    void Talk()
    {
        cout << "Cat : 야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹!" << endl;
    }
};

class Tiger : public Cat
{
public:
    Tiger()
    {
        cout << "Tiger : 크아앙(탄생)" << endl;
    }
    ~Tiger()
    {
        cout << "Tiger : 컼(죽음)" << endl;
    }

    /*void Roar()
    {
        cout << "Tiger : 영어를 잘해야 외국인을 만남..." << endl;
    }*/
    void Talk()
    {
        cout << "Tiger : 영어를 잘해야 외국인을 만남..." << endl;
        //endl : 자동 줄 바꿈
    }
};

int main()
{
    //정적 할당
    cout << "냐옹앱 시작" << endl;
    cout << endl;

    /*Cat* c;
    c->Meow();
    delete(c);*/

    /*Tiger* c = new Tiger();
    c->Roar();
    delete(c);*/

    //객체지향
    //Cat* c = new Tiger();
    //Tiger* t = (Tiger*)c; //c를 t로 형변환
    //t->Meow();
    //t->Roar();
    //delete(t);

    int AnimalNum = 3;
    Animal** ani = new Animal * [AnimalNum];

    ani[0] = new Tiger();
    ani[1] = new Cat();
    ani[2] = new Hamster();

    for (size_t i = 0; i < AnimalNum; i++)
    {
        ani[i]->Talk();
        delete(ani[i]);
    }
}
//객체 생성
//실행
//소멸

//메모리는 스택 구조
//스택 : last in first out
//정적할당

//동적할당
//자신이 원하는 대로 메모리 할당
//지우는 것도 자신의 선택과 집중-> 힙
//메모리를 제대로 삭제하지 않으면 메모리누수 발생
//메모리를 덮어쓰는 것을 메모리침범이라고 함

//클래스 -> 주소값의 개념과 일맥 상통
//객체는 참조로
//2023-04-17