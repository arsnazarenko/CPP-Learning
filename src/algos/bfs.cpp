#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

void bfs(int32_t v, std::vector<std::vector<int32_t>> const& graph, std::vector<char>& color) {
    std::queue<int32_t> q;
    q.push(v);
    color[v] = 1;
    while (!q.empty()) {
        //  извлекаем вершину из очереди и доабвляем
        //  в очередь все смежные необработанные (нераскрашенные) смежные к ней вершины
        //  и закрашиваем их
        int32_t vert = q.front();
        q.pop();
        for (int32_t u : graph[vert]) {
            if (color[u] == 0) {
                q.push(u);
                // раскрашиваем вершину
                color[u] = 1;
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
    std::cin >> start--;
    assert(start >= 0 || start < n);
    for (size_t i = 0; i < n; ++i) {
        std::cout << (i + 1) << ": ";
        for (int32_t ver: graph[i]) {
            std::cout << (ver + 1) << " ";
        }
        std::cout << "\n";
    }
    std::vector<char> color(n);
    bfs(start, graph, color);
    for(char i : color) {
        std::cout << static_cast<int32_t>(i) << " ";
    }
    return 0;
}

