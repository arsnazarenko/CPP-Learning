#include <iostream>
#include <vector>
#include <cassert>
//  0 - черный (не обработана)
//  1 - красный (вершина просмотрена)
//  2 - зеленая (вершина просмотрена и все смежные с ней тоже)
bool dfs(int32_t v, std::vector<std::vector<int32_t>> const &graph, std::vector<char> &color) {
    //  красим в красный при входе в вершину

    color[v] = 1;
    //  пробегаясь по каждой смежной вершине к текущей
    for (int32_t u: graph[v]) {
        if (color[u] == 1) {
            // если вершина уже красная => найден цикл
            return true;
        }   // вершина еще не обработана
        if (color[u] == 0) {
            bool loop_found = dfs(u, graph, color);
            if (loop_found) return true;    // при обходе графа начиная с этой ветки найден цикл
        }
    }   //  иначе среди смежных веток цикл не нпйден, красим в зеленый
    color[v] = 2;
    return false;
}




//  Алгоритм Дейкстры для поиска кратчайшего пути в графе
int main() {
    int32_t n;
    std::cin >> n;
    std::vector<std::vector<int32_t>> graph(n);
    std::vector<char> color(n);
    // ориентированный граф
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            int32_t t;
            std::cin >> t;
            if (t == 1) {
                graph[i].push_back(j);
            }
        }
    }
    bool loop_found = false;
    for (int32_t i = 0; i < n; ++i) {
        if (color[i] == 0) {
           if (dfs(i, graph, color)) {
               loop_found = true;
               break;
           }
        }
    }
    std::cout << (loop_found ? "yes" : "no");
    return 0;
}