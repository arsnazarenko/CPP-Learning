#include <iostream>
#include <vector>

const int inf = 1e9;

void algo_paths(int n, int m, int v, std::vector<edge> const& e, std::vector<int> &distance) {
    distance[v] = 0;
    // делаем бесконечный цикл, т.к в зависимости от порядка обхода вершин,
// алгоритм может дать верный ответ меньше , чем за n-1 фазу,
// поэтому если на одной из фаз не произошло никаких
// релаксаций, то можно вызодить из цикла
    for(int k = 0; k < (n - 1); ++k) {
        bool any = false;
        for (int j = 0; j < m; ++j) {
            //  отрицательные ребра могут улучшить путь до недостежимыъ вершин
            //  к примеру, путь будет (inf - 1), поэтому не будем улучшать такие ребра
            //  если вершина достижима
            if (distance[e[j].a] < inf) {
                if (distance[e[j].b] > distance[e[j].a] + e[j].cost) {
                    distance[e[j].b] = distance[e[j].a] + e[j].cost;
                    //  метка релаксации на текущей фазе
                    any = true;
                }
            }
        }
        //  если на этой фазе не было релаксаций, break
        if (!any) { break; }
    }
}

bool algo_cycle(int n, int m, int v, std::vector<edge> const& e, std::vector<int> &distance) {
    distance[v] = 0;
    // делаем бесконечный цикл, т.к в зависимости от порядка обхода вершин,
// алгоритм может дать верный ответ меньше , чем за n-1 фазу,
// поэтому если на одной из фаз не произошло никаких
// релаксаций, то можно вызодить из цикла
    bool relax = false;
    for(int k = 0; k < n; ++k) {
        relax = false;
        for (int j = 0; j < m; ++j) {
            //  отрицательные ребра могут улучшить путь до недостежимыъ вершин
            //  к примеру, путь будет (inf - 1), поэтому не будем улучшать такие ребра
            //  если вершина достижима
            if (distance[e[j].a] < inf) {
                if (distance[e[j].b] > distance[e[j].a] + e[j].cost) {
                    distance[e[j].b] = distance[e[j].a] + e[j].cost;
                    relax = true;
                }
            }
        }
    }
    if (relax) return true;
    return false;
}

int main() {
    //  ребра
    int n;
    //  вершины
    int m;
    //  стартовая вершина
    int v;
    std::cin >> n >> m >> v;
    v--;
    std::vector<edge> e;
    for (int i = 0; i < m; ++i) {
        int a, b, cost;
        std::cin >> a >> b >> cost;
        a--;
        b--;
        e.emplace_back(a, b, cost);
    }
    std::vector<int> distance(n, inf);
    std::cout << algo_cycle(n, m, v, e, distance);
//    for (int i = 0; i < n; ++i) {
//        std::cout << (i + 1) << ":" << distance[i] << "\n";
//    }
}


