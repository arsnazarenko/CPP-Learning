#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using i32 = int64_t;
const i32 inf = 1000 * 1000 * 1000;


void dijkstra_queue(size_t n, size_t s, size_t f, std::vector<std::vector<int32_t>> const& graph);

int main() {
    size_t n, s, f;
    std::cin >> n >> s >> f;
    s--;
    f--;
    std::vector<std::vector<int32_t>> graph(n, std::vector<i32>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cin >> graph[i][j];
        }
    }

    //  дистанция от старотовой вершины ко всем остальным
    dijkstra_queue(n, s, f, graph);
    return 0;
}

void dijkstra_queue(size_t n, size_t s, size_t f, const std::vector<std::vector<int32_t>> &graph) {
    std::vector<i32> distance(n, inf);
    std::vector<i32> pr(n, -1);
    distance[s] = 0;
    std::priority_queue<std::pair<i32, i32>> q;
    q.emplace(0, s);
    while (!q.empty()) {
        i32 len = -(q.top().first);
        i32 v = q.top().second;
        q.pop();
        //  в очереди мгут быть фиктивные вершины из-за отсутствия операции обновления ключа,
        //  поэтому требуется проверка
        if (len > distance[v]) continue;
        for (size_t i = 0; i < n; ++i) {
            size_t to = i;
            i32 length = graph[v][i];
            if (distance[to] > distance[v] + length && length >= 0) {
                distance[to] = distance[v] + length;
                pr[to] = v;
                q.push(std::make_pair(-(distance[to]), to));
            }
        }
    }
    if (distance[f] == inf) {
        std::cout << "-1";
    } else {
        std::cout << distance[f] << "\n";
        std::vector<i32> path;
        size_t cur = f;
        path.push_back(f);
        while (pr[cur] != -1) {
            cur = pr[cur];
            path.push_back(cur);
        }
        std::reverse(path.begin(), path.end());
        for (int32_t v: path) {
            std::cout << v + 1 << " ";
        }
    }


}
