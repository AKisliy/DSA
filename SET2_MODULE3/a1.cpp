//
// Created by alexe on 12.03.2024.
//
#include <iostream>
#include <vector>
#include <unordered_set>
#include <random>

// -----------------------< Infrastructure stuff > --------------------------------------------
class Edge{
public:
    int from;
    int to;
    int weight;
    Edge() {}
    Edge(int from, int to, int weight){
        this->from = from;
        this->to = to;
        this->weight = weight;
    }

    bool operator==(const Edge &other) const{
        return from == other.from && to == other.to && weight == other.weight;
    }
};

// mock class to escape errors
class Graph{
public:
    std::vector<std::vector<Edge>> graph;
    std::vector<Edge> edges;
    std::vector<int> vertices;
};

class UnionFind
{
public:
    std::vector<int> parent;
    std::vector<int> size;
    int maxSize;
    UnionFind(int n): parent(n), size(n)
    {
        maxSize = 1;
        // Вначале каждая вершина - сама себе родитель
        for(int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findParent(int x)
    {
        if (x != parent[x])
            parent[x] = findParent(parent[x]);
        return parent[x];
    }
    // объединяем вершины
    bool Union(int x, int y)
    {
        int rootX = findParent(x);
        int rootY = findParent(y);
        // если они не с одного множества, то ок
        if(rootX != rootY)
        {
            // мы всегда хотим, чтобы бОльшее множество
            // съедало меньшее
            // Поэтому мы всегда делаем так, чтобы множество X было больше.
            if (size[rootX] < size[rootY])
            {
                // использовали кортеж для swap
                (rootX, rootY) = (rootY, rootX);
            }
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
            maxSize = std::max(maxSize, size[rootX]);
            return true;
        }
        // оказались с одного множества - получаем цикл(плохо)
        return false;
    }
};

bool compEdges(const Edge& e1, const Edge& e2){
    return e1.weight < e2.weight;
}

struct pair_hash{
    template<class T1, class T2>
    size_t operator() (const std::pair<T1, T2> &pair) const{
        auto h1 = std::hash<T1>{}(pair.first);
        auto h2 = std::hash<T2>{}(pair.second);
        return h1 ^ h2;
    }
};

template<>
struct std::hash<Edge>{
    size_t operator()(const Edge& edge) const{
        return std::hash<int>()(edge.from);
    }
};

bool isConnectedAfterRemoval(Graph g,const std::unordered_set<Edge> remainingEdges, int removeFrom, int removeTo){
    // логика проверки связности с помощью BFS
    // (не забывая в BFS проходить только по доступны ребрам(проверка работает за O(1))
    // и не проходить по {removeFrom, removeTo}
    return true; // заглушка
}

std::pair<int, Edge> findCycle(int node, int parent, Graph g, const std::unordered_set<Edge>& edges, std::vector<bool>& visited){
    // нашли цикл
    if(visited[node]){
        return {node, Edge(-1, -1, INT32_MIN)};
    }
    visited[node] = true;
    for(auto edge: g.graph[node]){
        if(edges.contains(edge)){ // O(1)
            if(edge.to != parent) {
                auto k = findCycle(edge.to, edge.from, g, edges, visited);
                // сосед оказался в цикле
                if (k.first != -1) {
                    return {k.first, k.second.weight > edge.weight ? k.second : edge};
                }
            }
        }
    }
    // вершина не в цикле
    return {-1, Edge{}};
}

// ------------------------< Main task>----------------------------------





std::unordered_set<Edge> alg1(Graph g){
    std::vector<Edge> edges(g.edges);
    // сортируем ребра
    std::sort(edges.begin(), edges.end(), compEdges);
    // T
    std::unordered_set<Edge> T(g.edges.begin(), g.edges.end());
    for(Edge e: edges){
        if(isConnectedAfterRemoval(g, T, e.from, e.to))
            T.erase(e);
    }
    return T;
}

std::vector<Edge> alg2(Graph g){
    std::vector<Edge> edges(g.edges);
    size_t m = edges.size();
    // крайний случай - если нет ребер
    if(m == 0){
        return edges;
    }
    // создаем генератор
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, m - 1);

    // храним посещенные дуги и их количество
    std::vector<bool> visited(m);
    size_t visited_count = 0;

    // создаем T
    std::vector<Edge> result;
    // будем использовать UnionFind
    UnionFind u(g.vertices.size());

    for(size_t index = distribution(gen); visited_count != m; index = distribution(gen)){
        if(visited[index])
            continue;
        visited[index] = true;
        ++visited_count;
        auto e = edges[index];
        // если получилось без циклов - добавляем в результат
        if(u.Union(e.from, e.to)){ // за счет эвристик union работает за О(1)
            result.push_back(e);
        }
    }
    return result;
}


std::unordered_set<Edge> alg3(Graph g) {
    size_t m = g.edges.size();
    size_t n = g.vertices.size();
    std::unordered_set<Edge> result;
    // крайний случай - если нет ребер
    if(m == 0)
        return result;

    UnionFind uf(g.vertices.size());

    // создаем генератор
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, m - 1);

    // храним посещенные дуги и их количество
    std::vector<bool> visited(m);
    size_t visited_count = 0;

    std::vector<Edge> edges(g.edges.begin(), g.edges.end());

    for(size_t index = distribution(gen); visited_count != m; index = distribution(gen)){
        if(visited[index])
            continue;
        visited[index] = true;
        ++visited_count;
        Edge e = edges[index];
        result.insert(e);
        if (!uf.Union(e.from, e.to)) {
            // Если ребро создаёт цикл, находим максимальное ребро в этом цикле.
            std::vector<bool> visitedVertices(n);
            Edge maxEdgeInCycle = findCycle(e.from, -1, g, result, visitedVertices).second;
            // Удаляем максимальное ребро из цикла.(амортизировано O(1))
            result.erase(maxEdgeInCycle);
        }
    }

    return result;
}

