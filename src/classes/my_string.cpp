#include "my_string.h"
#include <cstring>
#include <algorithm>

my_string::my_string(size_t sz, const char ch = '\0') : size(sz), buf(new char[size + 1]) {
    memset(buf, ch, size);
    buf[sz] = '\0';
}

my_string::my_string(const char *ch) : size(strlen(ch)), buf(new char[size + 1]) {
    strncpy(buf, ch, size + 1);
}

my_string::my_string(my_string const &str) : size(str.size), buf(new char[size + 1]) {
    strncpy(buf, str.buf, size + 1);
}

my_string::my_string(std::initializer_list<char> lst) : size(lst.size()), buf(new char[size + 1]) {
    std::copy(lst.begin(), lst.end(), buf);
    buf[size] = '\0';
}

//  компилируется, хотя по сути константный метод позволяет менять строку
//  так происходит, потому что в метод передается my_string const* - указатель на константный объект
//  это значит что мы не может изменять поля класса, значит поле char * станет char* const - неизменяемый указатель на
//  изменяемый объект, а значит операция присваивания по индексу будет работать корректно и изменить строку мы сможем
//  поэтому требуется определять два оператора []
char& my_string::operator[](size_t idx) {
    return buf[idx];
}

char my_string::operator[](size_t idx) const {
    return buf[idx];
}

//my_string &my_string::operator=(my_string const& str) {
//    if (this != &str) {
//        delete[] buf;
//        size = str.size;
//        buf = new char[size + 1];
//        strncpy(buf, str.buf, size + 1);
//    }
//    return *this;
//}

my_string& my_string::operator=(my_string const& str) {
    if (&str != this) {
        my_string(str).swap(*this);
    }
    return *this;
}


size_t my_string::length() const {
    return this->size;
}

my_string::~my_string() {
    delete[] buf;
}

void my_string::swap(my_string &str) {
    std::swap(size, str.size);
    std::swap(buf, str.buf);
}

std::ostream& operator<<(std::ostream& out, my_string const& s) {
    for (size_t i = 0; i < s.length(); ++i) {
        out << s[i];
    }
    return out;
}






