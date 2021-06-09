#ifndef MY_STRING
#define MY_STRING
#include <cstddef>
#include <initializer_list>
#include <ostream>

class my_string {
private:
    size_t size = 0;
    char* buf = nullptr;

    void swap(my_string& str);
public:
    my_string() = default;
    explicit my_string(size_t sz, char ch);
    explicit my_string(const char* ch);
    my_string(std::initializer_list<char> lst);

    my_string(my_string const& str);

    my_string& operator=(my_string const& str);

    char& operator[](size_t idx);
    char operator[](size_t idx) const;

    ~my_string();

    friend std::ostream& operator<<(std::ostream& out, my_string const& s);

    size_t length() const;
};

#endif