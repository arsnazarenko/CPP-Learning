#include <iostream>

//  multiply inheritance

namespace mul {
    struct Mother {

        int m = 1;
        int k = 4;

        void foo() {};
    };

    struct Father {

        int f = 2;
        int k = 6;

        void foo() {}
    };

    struct Son : public Mother, public Father {
        int s = 3;
    };

}
//  Diamond problem
namespace diamond {
    class Granny {
    public:
        int g = 0;
    };

    class Mother : public Granny {
    public:
        int m = 1;
    };

    class Father : public Granny {
    public:
        int f = 2;
    };

    class Son : public Mother, public Father {
        int s = 3;
    };
}

void multiply_inh() {
//  Для множественного наследования характерно то, что
//  указатель на объект будет разным в засимиости от того,
//  какой тип у указателя
//  К примеру, для указатель Father* указывающий на объект Son,
//  будет смещен на 4 байта относительно указателя Son* на тот же объект
//  Объект в памяти тем не менее один и тот же
//  При касте происходят сдвиги
/**
 * CLASS LAYOUT
 * [ Mother::m ][ Father::f ][ Son::s ]
 * */
    mul::Son s;
    std::cout << &s << "\n";
    mul::Father *pf = &s;
    std::cout << pf << "\n";
    std::cout << static_cast<mul::Son *>(pf)->s << "\n";

    mul::Father f;


    //  подвинем укаатель на 4 байта влево относительно адреса
//  father и посмотрим, что в памяти
    std::cout << "m: " << *((int *) (&f) - 1) << "\n";
    //  скастуем класс родитель к классу потомка, что неуместно
    std::cout << "m: " << static_cast<mul::Son &>(f).m << "\n";

    //  при таком касте никакого сдвига не будет, и запрашивая m мы увидим f
    std::cout << "m: " << reinterpret_cast<mul::Son &>(f).m << "\n";

    //  когда два класса одного уровня наследования (Father и Mother)
//  содержат одинаковые поля, то происходит неоднозначночть
//  аналогично для функций
//fixme: s.k;
//fixme: s.foo();
//  НО!
    s.Father::foo();
    s.Mother::foo();
    s.Father::k;
    s.Mother::k;
}

int main() {
    multiply_inh();

    return 0;
}