#include <iostream>
#include <vector>
#include <cassert>



int64_t parent(int64_t i) {
    return (i - 1) / 2;
}

int64_t left_child(int64_t i) {
    return 2 * i + 1;
}

int64_t right_child(int64_t i) {
    return 2 * i + 2;
}

void sift_up(int64_t v, std::vector<int64_t>& heap) {
    int64_t current_idx = v;  //индекс элемента, который просеиваем вверх
    while(heap[current_idx] < heap[parent(current_idx)]) {
        std::swap(heap[current_idx], heap[parent(current_idx)]);
        current_idx = parent(current_idx);
    }
}
//  добавили новй элемент в конец, просеили его навех
void insert(int64_t value, std::vector<int64_t>& heap) {
    heap.push_back(value);
    sift_up((heap.size()) - 1, heap);
}

void sift_down(int64_t i, std::vector<int64_t>& heap) {
    int64_t current_idx = i;
    while (true) {
        //  если существует левый потомок и элемент меньше, чем его левый потомок
        if (left_child(i) < heap.size() && heap[current_idx] > heap[left_child(i)]) {
            current_idx = left_child(i);
        }
        // если существует правый правый потомок и левый потомок меньше чем правый
        if (right_child(i) < heap.size() && heap[current_idx] > heap[right_child(i)]) {
            current_idx = right_child(i);
        }
        //  если элемент изначально стоял на своей позиции
        if (i == current_idx) break;
        //  иначе меняем элементы
        std::swap(heap[i], heap[current_idx]);
        i = current_idx;
    }
}
// обменяли вершину пирамиды с последним элементом, просеили вниз вершину (перестроили пирамиду)
// извлекли последний элемент
int64_t extract_min(std::vector<int64_t>& heap) {
    int64_t max = heap.front();
    std::swap(heap.front(), heap.back());
    heap.pop_back();
    sift_down(0, heap);
    return max;
}

void decrease_key(int64_t old_value, int64_t new_value, std::vector<int64_t>& heap) {
    assert(new_value <= new_value);

}

int64_t get_min(std::vector<int64_t>& heap) {
    return heap[0];
}
//  начиная с правого элемента предпоследнего ряда у которого есть дети
//  рассматриваем этого родителя как корень поддерева и посеиваем его вниз
void build_heap(std::vector<int64_t>& array) {
    for (int64_t i = (array.size() / 2 - 1); i >= 0; --i) {
        sift_down(i, array);
    }
}

int main() {
    std::vector<int64_t> heap(20);
    for (int64_t& el: heap) {
        std::cin >> el;
    }
    std::cout << std::endl;
    build_heap(heap);
    for (int64_t const& el: heap) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    insert(100, heap);
    for (int64_t const& el: heap) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    std::cout << "max: " <<  extract_min(heap);
    std::cout << std::endl;

    for (int64_t const& el: heap) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    while (!heap.empty()) {
        std::cout << extract_min(heap) << " ";
    }
    return 0;

}
