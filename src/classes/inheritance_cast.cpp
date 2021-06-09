#include <iostream>
namespace cast {

    class Base {
    private:
        int a = 0;
    public:
        Base() = default;
        Base(Base const& base) {
            std::cout << "copy Base\n";
        }
    };
    class Derived : public Base {
    private:
        int b = 1;
    public:
        Derived() = default;
        Derived(Derived const& derived) {
            std::cout << "copy derived\n";
        }
    };

    void g(Derived& d) {};
    void f(Base& d) {};
}

int main() {
    cast::Derived d;
    cast::Base& b = d;
    cast::f(d);
    cast::f(b);
    //  Копирование часть Derived, которая является Base
    //  Срезка (slicing)
    cast::Base b1 = d;
    cast::Base* pb = &d;
    cast::Derived& d1 = static_cast<cast::Derived&>(b1);
    cast::g(d1);
    cast::f(b1);
    return 0;

}