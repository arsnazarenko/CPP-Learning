#include "my_string.h"


int main() {
    const my_string c("Hello");
    my_string b(10, 'n');
    b[0] = 'k';
    return 0;
}