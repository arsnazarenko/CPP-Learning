#include <iostream>
#include <cstdlib>

//  Указатели и ссылки


// Преимущество ссылок над указателями -
// мы точно знаем, что пришел в аргумент объект,
// а не nullptr
void changeViaRef(int64_t&);
void changeViaPtr(int64_t*);
void workViaConstRef(const int64_t&);
struct Something {
    int64_t value;
    float value2;
};

struct Other {
    Something something;
    int64_t otherValue;
};


int main() {
    int64_t a = 256;
    int64_t b = 1024;

    //  Указатели
    //  nullptr - нововведение c++, для указателей, не ссылающихся
    //  на какую либо область памяти предпочтителен именно он, нежели NULL
    int64_t* ptr = nullptr;
    ptr = &a;
    std::cout << "addr: " << std::hex << ptr
              << ", value: " << std::dec << *ptr << std::endl;
    ptr = &b;
    std::cout << "addr: " << std::hex << ptr
              << ", value: " << std::dec << *ptr << std::endl;


    //  Const
    //  Нельзя изменить значение на
    //  протяжении всего жизненного цикла этих данных
    //
    //  Обязательно инициализировать при объявленни
    //  Указатель на такой объект обязательно должен быть const* !!!
    const int64_t c_a = 228;

    //fixme: int64_t* bad_ptr = &c_a;    - ERROR, неконстантный указатель указывает на констаный объект


    // - нельзя изменить значение объекта через разыменование,
    // - можно изменить значение самого указателя, указав,
    // что теперь он ссылкается на другую область памяти
    const int64_t* ptr_const_value = &c_a;
    //fixme:    *ptr_const_value = 4; - ERROR
    ptr_const_value = &b; // - OK


    // - можно изменить значение объекта через разыменование,
    // - нельзя изменить значение самого указателя, указав,
    // что теперь он ссылкается на другую область памяти
    int64_t* const ptr_const = &a;
    *ptr_const = 228;    // - OK
    //fixme:  ptr_const = &b; - ERROR


    // - нельзя изменить значение объекта через разыменование,
    // - нельзя изменить значение самого указателя, указав,
    // что теперь он ссылкается на другую область памяти
    const int64_t* const const_const_ptr = &c_a;
    //fixme:  *const_const_ptr = 24; - ERROR
    //fixme:  const_const_ptr = &b; - ERROR


    int64_t c = 1337;
    int64_t d = 1488;
    const int64_t e = 812;
    std::cout << std::endl;


    //  Ссылка - псевдоним объекта
    //  Обязательное условие для ссылки - при объявлении
    //  переменной обязательно должна быть проинициализирована !!!
    //fixme:  int32_t& ref; - ERROR


    // До конца своей жизни ссылка ссылается на один объект !!!
    // Ссылки на неконстантные значения могут быть инициализированы
    // только неконстантными l-values
    int64_t& ref = c;   //OK, т к с - неконстантное l-value
    //fixme:  int64_t& bad_ref = 9;   //ERROR, т к с - не l-value


    // так как ссылка - псевдоним для объекта, для получения адреса,
    // на который указывает ссылка , аналогично используется
    // оператор получения адреса &
    std::cout << "Before change" << std::endl
              << "ref addr: " << std::hex << &ref
              << "ref value: " << std::dec << ref << std::endl;
    //  Здесь мы по ссылке ref изменяем объект c,
    //  на который ссылка ссылалась
    //  Теперь ссылка не ссылается на объект d,
    //  она копирует значение d в c!!
    ref = d;
    std::cout << "After change via ref" << std::endl
              << "ref addr: " << std::hex << &ref
              << "ref value: " << std::dec << ref << std::endl;


    // ссылки на константные значения могут быть инициализированы
    // неконстантными l-values, константными l-values и r-values:
    // Изменить объект через константную ссылку невозможно (почти)
    // Аналоично указателям, неконстантная ссылка
    // не может указывать на константный объект,
    // так как могла бы изменить его, что нарушает понятие const
    //fixme: int64_t& const_ref = e; - ERROR

    const int64_t& const_ref = e; // - OK, константное l-value
    const int64_t& const_ref2 = c; // - OK, неконстантное l-value

    //  Цикл жизни r-value - одно выражение, после которого оно уничтожается
    //  Однако, если константная ссылка нициализируется значением r-value,
    //  то время жизни r-value продлевается в соотвествии со временем жизни ссылки
    const int64_t& const_ref1 = 4; // - OK, r-value
    std::cout << const_ref1 << std::endl;

    std::cout << "c: " << c << std::endl;
    changeViaRef(c);
    std::cout << "c: " << c << std::endl;
    changeViaPtr(&c);
    std::cout << "c: " << c << std::endl;
    workViaConstRef(c);


    Something s = (Something) {.value = 123, .value2 = 0.1};
    Other o = (Other) {.something = s, .otherValue = 1000};

    //Если надо несколько раз изменить значение этой переменной
    o.something.value = 56;  // - неудобно
    int64_t& ref_value = o.something.value;
    ref_value = 28; // - намного удобнее

    // foreach #1
    int64_t math[] = { 0, 1, 4, 5, 7, 8, 10, 12, 15, 17, 30, 41};
    for (int64_t number : math)  {
        //  здесь в number каждый раз копируется элемент массива,
        //  его изменение ни к чему не приведет в самом массиве
        std::cout << number << ' ';
    }
    std::cout << std::endl;

    // foreach #2
    for (int64_t& number : math)  {
        //  здесь рвботает с элеентами через ссылку без копирования
        //  элементов, есть возможность их изменить
        std::cout << number << ' ';
    }
    std::cout << std::endl;

    // foreach #3 - best
    for (const int64_t& number : math)  {   // можно так: const auto&
        //  здесь рвботает с элеентами через конст. ссылку без копирования
        //  без возможности их изменить
        std::cout << number << ' ';
    }
    std::cout << std::endl;
    return 0;
}


void changeViaRef(int64_t& a) {
    a = 2048;
}

void changeViaPtr(int64_t* int_ptr) {
    *int_ptr = 4096;
}
//  Ссылки, используемые в качестве параметров функции, также могут быть константными.
//  Это позволяет получить доступ к аргументу без его копирования, гарантируя, что функция
//  не изменит значение, на которое ссылается ссылка
//  Правило: Переменные не фундаментальных типов данных и которые не являются
//  указателями, передавайте в функцию по (константной) ссылке.
void workViaConstRef(const int64_t& c_value) {
    std::cout << c_value << std::endl;
}