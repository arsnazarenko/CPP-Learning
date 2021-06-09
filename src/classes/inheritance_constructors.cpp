#include <iostream>
namespace construct {
    class A {
    public:
        A() {
            std::cout << "A()";
        }
        ~A() {
            std::cout << "~A()";
        }
    };
    class B {
    public:
        B() {
            std::cout << "B()";
        }
        ~B() {
            std::cout << "~B()";
        }
    };

    class Base {
    public:
        int32_t x = 0;
        A a;
        Base() {
            std::cout << "Base()";
        }

        Base(int32_t x) : x(x) {std::cout << "Base(int32_t)";};

        ~Base() {
            std::cout << "~Base()";
        }
    };

    class Derived : public Base {
    public:
        const size_t n;
        double y = 0.;
        B b;
        Derived(size_t n) : n(n) {
            std::cout << "Derived()";
        }
        //  нужно соблюдать порядок:
        //  как в списках инициализации - в порядке объявления полей и
        //  поля родительских классов инициализируются первыми
        Derived(int32_t x, size_t n, double y) : Base(x), n(n), y(y) {std::cout << "Derived(int32_t, double)";};

        ~Derived() {
            std::cout << "~Derived()";
        }
    };

}
int main() {
    construct::Derived d(5, 1024, 9.9);

    return 0;
}