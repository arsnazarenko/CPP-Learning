#include <iostream>


void merge(int64_t* array, int64_t* aux, int32_t l, int32_t m, int32_t r) {
    int32_t i = l;
    int32_t j = m + 1;

    //  копирования массива во временный, сортируем во временном, заполняем исходный
//    for (int32_t k = l; k <= r; ++k) { aux[k] = array[k]; }

    for (int32_t k = l; k <= r; ++k) {
        //  если левый указатель уже жакончил свой проход,
        //  то мы последовательно дозаполняем массив правым
        //  отсортированным подмассивом
        if (i > m) {array[k] = aux[j++]; continue;}
        //  если правый указатель уже жакончил свой проход,
        //  то мы последовательно дозаполняем массив левым
        //  отсортированным подмассивом
        if (j > r) {array[k] = aux[i++]; continue;}
        if (aux[j] < aux[i]) {array[k] = aux[j++];}
            //  Стабильна!
        else    {array[k] = aux[i++];}
    }
}



void merge_sort(int64_t* arr, int64_t* aux, int32_t l, int32_t r) {
    if (l < r) {
        int32_t m = (r + l)/2;
        merge_sort(aux, arr, l, m);
        merge_sort(aux, arr, m+1, r);
        merge(arr, aux, l, m, r);
    }
}

void sort(int64_t* array, int32_t size) {
    int64_t* aux = new int64_t[size];
    for (int32_t k = 0; k < size; ++k) {
        aux[k] = array[k];
    }
    merge_sort(array, aux, 0, size-1);
    delete[] aux;
}

void print_array(int64_t const* array, int32_t size) {
    for (int32_t i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
}



int main() {
    int32_t size;
    std::cin >> size;
    int64_t* a = new int64_t[size];
    for (int32_t i = 0; i < size; ++i) {
        std::cin >> a[i];
    }
    sort(a, size);
    print_array(a, size);
    delete[] a;
    return 0;
}




