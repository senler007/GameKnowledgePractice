#include<iostream>
class A {
private:
    char a = 5;
    int  b = 5;

public:
    int  getB() {
        return b;
    }
};

int main() {
    A a;
    char* p = reinterpret_cast<char*>(&a);
    *(p + 1) = 5;

    std::cout << a.getB() << "         +++++";
}