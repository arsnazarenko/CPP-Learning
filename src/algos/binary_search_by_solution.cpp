#include <iostream>

void diploms() {
    int32_t w, h, n;
    std::cin >> w >> h >> n;
    uint64_t left = 0;
    //  здесь может быть значене равное 10^9 * 10^9 ~ 2^60, тип uint64_t допускает это
    //  но при вычислении обе переменные int32_t, значит и результат будет представлен в int32
    uint64_t right =  1LL + std::max(w, h) * n;
    while(right - left > 1) {
        uint64_t mid = (left + right) / 2;
        if ((mid / w) * (mid / h)  < n) {
            left = mid;
        } else {
            right = mid;
        }
    }
    std::cout << right << '\n';
}


void cows() {

}

int main() {
    diploms();
    return 0;
}