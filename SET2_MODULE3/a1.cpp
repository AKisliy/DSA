//
// Created by alexe on 22.03.2024.
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

bool isConnected(Graph g,const std::unordered_set<std::pair<int,int>, pair_hash>& deleted ){
    // логика проверки связности с помощью BFS
    // (не забывая в BFS проверять удаленные ребра(работает за O(1))
    return true; // заглушка
}

Edge* findCycle(Graph g, const std::unordered_set<Edge>& edges){
    // можно искать цикл с помощью DFS(учитывая только включенные ребра)
    // в alg3 у нас он гарантировано если и будет, то единственный
    // при развороте рекурсии можно найти и самое тяжелое ребро
    return nullptr;
}

// ------------------------< Main task>----------------------------------





std::vector<Edge> alg1(Graph g){
    std::vector<Edge> edges(g.edges);
    // сортируем ребра
    std::sort(edges.begin(), edges.end(), compEdges);
    // какие ребра были удалены
    std::unordered_set<std::pair<int,int>, pair_hash> deleted;
    // Т
    std::vector<Edge> result;
    for(Edge e: edges){
        if(isConnected(g, deleted))
            deleted.insert({e.from, e.to});
    }
    // формируем T
    for(Edge e: edges){
        if(!deleted.contains({e.from, e.to}))
            result.push_back(e);
    }
    return result;
}

std::vector<Edge> alg2(Graph g){
    std::vector<Edge> edges(g.edges);
    size_t m = edges.size();
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

    for(size_t index = distribution(gen); visited_count != m;){
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

std::unordered_set<Edge> alg3(Graph g){
    std::vector<Edge> edges(g.edges);
    size_t m = edges.size();
    // создаем T
    std::unordered_set<Edge> result;
    
    if(m == 0){
        return result;
    }

    // создаем генератор
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, m - 1);

    // храним посещенные дуги и их количество
    std::vector<bool> visited(m);
    size_t visited_count = 0;

    for(size_t index = distribution(gen); visited_count != m;){
        if(visited[index])
            continue;
        visited[index] = true;
        ++visited_count;
        auto e = edges[index];
        result.insert(e);
        Edge* maxEdge = findCycle(g, result);
        if(maxEdge != nullptr){
            result.erase(*maxEdge);
        }
    }
    return result;
}

