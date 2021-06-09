#include <iostream>

class C {
private:
    //  инициализировать статическое поле значением нельзя внутри класса
    //  если это не const или не целочисленный тип
    static C* obj;
public:
    C() {};
    static C& getObject() {
        if (obj) return *obj;
        obj = new C();
        return *obj;
    }
    //  нужно заботиться об удалении объекта самостоятельно
    static void destroy() {
        delete obj;
    }
};

class B {
private:
    B() {};
public:
    //  Lazy initialization
    //  уничтожение после завершения программы
    static B& getObject() {
        static B instance;
        return instance;
    }
};

C* C::obj = nullptr;

int main() {
    C c = C::getObject();
    B b = B::getObject();
    C::destroy();
}


