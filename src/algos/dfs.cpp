#include <iostream>
#include <vector>
#include <cassert>

void dfs(int32_t v, std::vector<std::vector<int32_t>> const &graph,
         std::vector<char> &color) {
    //  красим в красный при входе в вершину
    color[v] = 1;
    //  пробегаясь по каждой смежной вершине к текущей
    for (int32_t u: graph[v]) {
        if (color[u] == 0) {
            //  рекурсивно запускаем метод для непосещённных вершин
            dfs(u, graph, color);
        }
    }
}




//  Алгоритм Дейкстры для поиска кратчайшего пути в графе
int main() {
    //  кол-во вершин
    size_t n;
    //  кол-во ребер
    size_t m;
    std::cin >> n >> m;
    std::vector<std::vector<int32_t>> graph(n);
    for (size_t i = 0; i < m; ++i) {
        int32_t f, s;
        std::cin >> f >> s;
        f--;
        s--;
        graph[f].push_back(s);
        graph[s].push_back(f);
    }
    int32_t start;
    std::cin >> start;
    start--;
    assert(start >= 0 || start < n);
    for (size_t i = 0; i < n; ++i) {
        std::cout << (i + 1) << ": ";
        for (int32_t ver: graph[i]) {
            std::cout << (ver + 1) << " ";
        }
        std::cout << "\n";
    }
    //  ракрасим каждую компоненту свзяности в разный цвет
    std::vector<char> color(n, 0);
    dfs(start, graph, color);
    std::cout << "result:\n";
    for (size_t i = 0; i < n; ++i) {
        std::cout << static_cast<int32_t>(color[i]) << " ";
    }
    return 0;
}