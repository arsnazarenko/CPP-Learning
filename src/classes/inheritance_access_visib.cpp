#include <iostream>
// Visibility and accessibility
class Base {
public:
    int b = -1;
    void foo() {
        std::cout << "foo: Base\n";
    }
    void g(double n) {
        std::cout << "g: Base, " << n << "\n";
    }

    void y(int n) {
        std::cout << "y: Base, " << n << "\n";
    }

    int a = 0;
    void f() {
        std::cout << "f: Base\n";
    }

private:
    int k = 10;
};

class Derived : public Base {
public:
    int a = 1;
    void f() {
        std::cout << "f: Der\n";
    }
    void g(int n) {
        std::cout << "g: Der, " << n << "\n";
    }

    using Base::y;
    // foo in Base - public, but foo in Derived - private,
    // and we have two declaration of function foo() - CE
    using Base::foo;
    //fixme: using Base::k; // CE
    void y(std::string const& n) {
        std::cout << "y: Der, " << n << "\n";
    }
private:
    int b = -2;
    void foo() {
        std::cout << "foo: Der\n";
    }
};

int main() {
    //  Функции и поля в классе наследнике являются более локальными, поэтому
    //  наследник как бы затмевает их своими реализациями
    Derived der;
    der.f();    //  Der
    std::cout << der.a << "\n"; //  1

    Base base;
    base.f();   //  Base
    std::cout << base.a << "\n"; // 0

    //  мы можем явно вызвать у наследника функции и поля родителя (если они public)
    //  даже если их имена одинковы
    der.Base::f();  //  Base
    std::cout << der.Base::a << "\n";   //  0

    //  Если работать с дочерним объектом по ссылке род. ссылке, то для компилятора
    //  будут видны только члены классса родителя, так как у нас нет никаких v_tables,
    //  чтобы понять, какую реализацию функции вызвать
    Base* der1 = new Derived;

    der1->f();  //  Base
    std::cout << der1->a << "\n";   //  0
    //  static cast не рекомендуется для таких приведений,
    //  однако в нашем варианте все нормально, так как der1 - объект класса Derived

    Derived* der2 = static_cast<Derived*>(der1);
    der2->f();  //  Der
    std::cout << der2->a << "\n";   //  1
    //  Но неявно такие члены класса нам не видны, и, если бы функции и поля в классе наследнике
    //  приватны, то не вызовутся из родительские реализации, будет CE, потому что
    //  члены дочернего класса нам ВИДНЫ, но НЕДОСТУПНЫ, а
    //  члены родительского класса ДОСТУПНЫ, но не видны
// fixme:
//    der.foo()    // CE
//    der.b()      // CE
    der.Base::foo();    //  Base
    std::cout << der.Base::b << "\n";    // - 1

    //  В род. классе есть перегрузка функии g от double, но она
    //  опять же не видна, поэтому не участвует в перегрузке
    der.g(1);   // g(int) Der
    der.g(2.5);   // g(int) Der и double приводится к int

    //  Но мы можем к дочерний класс привнести члены родителького
    //  с помощью using, тогда члены род. класса будут видны в насоеднике,
    //  участвовать в перегрузке, но сделать это можно только ля члено с модификаторами доступа
    //  public или protected
    der.y(1);
    der.y("Hello");

    //fixme:der.foo(); - CE
    return 0;
}