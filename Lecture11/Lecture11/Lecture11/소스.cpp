////예제
//#include <iostream>
//#include <string>
//
//class Object {
//private:
//    std::string name;
//
//public:
//    Object(const std::string& name) : name(name) {}
//
//    std::string get_name() const {
//        return name;
//    }
//
//    void set_name(const std::string& new_name) {
//        name = new_name;
//    }
//
//    void display() const {
//        std::cout << "Object name: " << name << std::endl;
//    }
//};
//
//int main() {
//    Object obj("Example");
//    obj.display();
//
//    std::string new_name;
//    std::cout << "새로운 이름을 입력하세요: ";
//    std::getline(std::cin, new_name);
//    obj.set_name(new_name);
//    obj.display();
//
//    return 0;
//}