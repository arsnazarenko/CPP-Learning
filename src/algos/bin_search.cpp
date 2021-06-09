#include <iostream>
#include <vector>

int64_t lin_search(int64_t const arr[], size_t size, int64_t x) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;

}

int64_t bin_search(int64_t const arr[], int64_t size, int64_t x) {
    int64_t left = 1;
    int right = size;
    while (right - left > 1) {
        int64_t middle = (left + right) / 2;
        if (arr[middle] > x) {
            right = middle;
        } else  {
            left = middle;
        }
    }
    if (arr[left] == x) {
        return left;
    } else {
        return -1;
    }
}



int main() {
    size_t N = 20;
    int64_t arr[] = {1, 2, 12, 21, 34, 54, 65, 71, 72, 73, 80, 99, 101, 140, 199, 202, 250, 290, 333, 666};
    int64_t x;
    for (int64_t const &el: arr) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    std::cin >> x;
    std::cout << bin_search(arr, N, x) << std::endl;

    return 0;
}