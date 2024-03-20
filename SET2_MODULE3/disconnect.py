import networkx as nx


def disconnect(G, u, v) -> int:
    # Проверяем, что u и v не соседи
    for neighbour in G[u]:
        if neighbour == v:
            return -1

    # Строим копию
    H = nx.DiGraph()
    for edge in G.edges():
        H.add_edge(edge[0], edge[1], capacity=1)

    # Поиск максимального потока в копии
    max_flow_value = nx.maximum_flow_value(H, u, v)

    return max_flow_value


# Примеры использования
G = nx.DiGraph()
G.add_edge(1, 2)
G.add_edge(1, 3)
G.add_edge(2, 3)
G.add_edge(2, 4)
G.add_edge(3, 4)

print(f"Необходимо удалить {disconnect(G, 1, 4)} вершин, чтобы разорвать связь между 1 и 4")

G1 = nx.DiGraph()
G1.add_edge('S', 'A', capacity=3)
G1.add_edge('S', 'B', capacity=2)
G1.add_edge('A', 'C', capacity=3)
G1.add_edge('A', 'T', capacity=2)
G1.add_edge('B', 'T', capacity=3)
G1.add_edge('C', 'B', capacity=1)
G1.add_edge('C', 'T', capacity=1)
print(f"Необходимо удалить {disconnect(G1, 'S', 'T')} вершин, чтобы разорвать связь между S и T")

G2 = nx.DiGraph()
G2.add_edge('A', 'B', capacity=3)
G1.add_edge('A', 'C', capacity=1)
G1.add_edge('A', 'D', capacity=5)
G1.add_edge('B', 'E', capacity=3)
G1.add_edge('C', 'E', capacity=1)
G1.add_edge('D', 'E', capacity=7)
G1.add_edge('E', 'F', capacity=1)
print(f"Необходимо удалить {disconnect(G1, 'A', 'F')} вершин, чтобы разорвать связь между A и F")
