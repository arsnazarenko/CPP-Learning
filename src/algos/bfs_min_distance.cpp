#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

void bfs(int32_t v, std::vector<std::vector<int32_t>> const& graph, std::vector<int32_t>& depths) {
    std::queue<int32_t> q;
    q.push(v);
    // слой, на котором расположена первая вершина
    // (нумеруем с 1, потому что 0 - это состояние, когда слой не посчитан)
    depths[v] = 1;
    while (!q.empty()) {
        //  извлекаем вершину из очереди и доабвляем
        //  в очередь все смежные необработанные смежные к ней вершины
        //  и вычисляем слои для них
        int32_t vert = q.front();
        q.pop();
        for (int32_t u : graph[vert]) {
            if (depths[u] == 0) {
                q.push(u);
                // раскрашиваем вершину
                depths[u] = depths[vert] + 1;
            }
        }
    }
}

//  алгоритм обхода графа в ширину ( только для невзвешенных графов)
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
    std::vector<int32_t> depths(n, 0);
    bfs(start, graph, depths);
    for(int32_t i : depths) {
        std::cout << static_cast<int32_t>(i) << " ";
    }
    return 0;
}

