# не гарантирует однозначное восстановление
def restoreGraph(dist):
    n = len(dist)
    adjacency_list = {i: [] for i in range(n)}

    for i in range(n):
        for j in range(n):
            if i != j and dist[i][j] != float('inf'):  # Исключаем петли и точно не существующие ребра
                edge_exists = True
                for k in range(n):
                    # Проверяем равенство для каждой третьей вершины k
                    if k != i and k != j and dist[i][j] == dist[i][k] + dist[k][j]:
                        edge_exists = False
                        break
                if edge_exists:
                    # Добавляем ребро в список смежности, если оно удовлетворяет условиям
                    adjacency_list[i].append((j, dist[i][j]))

    return adjacency_list


# Пример использования
dist = [
    [0, 2, 3],
    [float('inf'), 0, 1],
    [float('inf'), float('inf'), 0]
]
graph = restoreGraph(dist)
print(graph)
