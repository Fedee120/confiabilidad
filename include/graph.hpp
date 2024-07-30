#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <utility>
#include <random>

class Graph {
public:
    Graph() = default;
    Graph(const std::string& filename);

    void load_graph(const std::string& filename);

    bool is_connected() const;

    // Método para muestrear el grafo con un generador de números aleatorios externo
    Graph sample_graph(std::mt19937& rng) const;

    // Método para obtener la lista de adyacencia
    const std::unordered_map<int, std::vector<std::pair<int, double>>>& get_adjacency_list() const;

    // Método para establecer la lista de adyacencia
    void set_adjacency_list(const std::unordered_map<int, std::vector<std::pair<int, double>>>& new_adjacency_list);

    void add_edge(int node1, int node2, double probability);

private:
    std::unordered_map<int, std::vector<std::pair<int, double>>> adjacency_list;

    void dfs(int node, std::unordered_map<int, bool>& visited) const;
};

#endif // GRAPH_HPP
