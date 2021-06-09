#include <iostream>
#include "raii_file.h"
int main() {
    raii_file test("../test.txt");
    char str[] = "Hello world, it's my program:)";
    test.write(str);
    return 0;
}