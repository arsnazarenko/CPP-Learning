
#include <iostream>

struct Complex {
//private:
    double re = 0.0;
    double im = 0.0;

public:
    Complex(double x = 0.0, double y = 0.0) : re(x), im(y) {};
    Complex(Complex const& complex) {
        re = complex.re;
        im = complex.im;
        std::cout << "copy" << "\n";
    }
    Complex& operator=(Complex const& complex) = default;
    ~Complex() = default;

    Complex& operator+=(Complex const& z) {
        re += z.re;
        im += z.im;
        return *this;
    }
    // префиксный инкремент
    Complex& operator++() {
        *this += 1;
        return *this;
    }

    //постфиксный инкремент
    //  (int) - фиктивный, только для отличия сигнатур постфиксного и префиксного инкремента
    //  возвращаем копию исходного объекта, а сам объект инкрементируем
    Complex operator++(int) {
        Complex copy = *this;
        ++(*this);
        return copy;
    }

};

//  оператор + лучше определять вне класса от двух переменных, чтобы
//  можно было делать так:
//  1. Complex a + (неявный каст) double b;
//  2. (неявный каст) double a + Complex b;

//fixme: version 1
// Complex operator+(Complex const& a, Complex const& b) {
//    Complex copy = a;
//    return copy += b;   //  2 копирования
// }

// version 2
// RVO optimization
Complex operator+(Complex const& a, Complex const& b) {
    Complex copy = a;
    copy += b;
    return copy;   //  1 копирование
}

bool operator<(Complex const& a, Complex const& b) {
    // для примера
    return a.re * a.re + a.im * a.im < b.re * b.re + b.im * b.im;
}

bool operator>(Complex const& a, Complex const& b) {
    return b < a;
}

bool operator==(Complex const& a, Complex const& b) {
    return !(b < a || a < b);
}

bool operator!=(Complex const& a, Complex const& b) {
    return !(a == b);
}



int main() {
    Complex c(2.0);
    Complex d(3.0, 1.0);
    // оператор += принимает Complex const&, а у нас справа double,
    // но компилятор делает неявный каст, так как есть конструктор Complex от 1 аргумента double
    c += 1.0;   //OK
    std::cout << c.re << ", " << c.im << "\n";

    std::cout << "operator sum with rvo\n";
    Complex sum = c + d;
    std::cout << sum.re << ", " << sum.im << "\n";

    std::cout << "post incr\n";
    sum++;
    std::cout << sum.re << ", " << sum.im << "\n";


    std::cout << "pref incr\n";
    ++sum;
    std::cout << sum.re << ", " << sum.im << "\n";

    return 0;
}


