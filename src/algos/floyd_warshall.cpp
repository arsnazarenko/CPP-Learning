#include <iostream>
#include <vector>

using ui32 = uint32_t;
using Graph = std::vector<std::vector<ui32>>;
const ui32 inf = 1e9;
int main() {
    size_t n;
    std::cin >> n;
    Graph graph(n, std::vector<ui32>(n));
    for (std::vector<ui32>& row : graph) {
        for (ui32& v : row) {
            std::cin >> v;
        }
    }
    // счетчик фаз - фаза (количество фаз = n)
    // каждая фаза подразумевает следующее:
    // на k фазе мы пробуем сделать пересчет расстояния между вершинами i и j:
    // i-------j,
    // включив промежуточную вершину k
    //     k
    //   /   \
    //  /     \
    // i-------j
    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
    ui32 max = 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            max = std::max(max, graph[i][j]);
        }
    }
    std::cout << max;
    return 0;
}