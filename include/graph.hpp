#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <string>

class Graph {
public:
    // Constructor predeterminado
    Graph() = default;

    // Constructor que carga el grafo desde un archivo CSV
    Graph(const std::string& filename);

    // Método que verifica si el grafo es conexo usando DFS iterativo
    bool is_connected() const;

    // Método que genera una muestra del grafo actual donde cada arista puede estar presente o no según su probabilidad de fallo
    Graph sample_graph() const;

    // Métodos para acceder y modificar la lista de adyacencia (para pruebas)
    void set_adjacency_list(const std::unordered_map<int, std::vector<std::pair<int, double>>>& adjacency_list);
    const std::unordered_map<int, std::vector<std::pair<int, double>>>& get_adjacency_list() const;

    // Método para añadir una arista
    void add_edge(int node1, int node2, double probability);

private:
    // Representación del grafo usando una lista de adyacencia
    std::unordered_map<int, std::vector<std::pair<int, double>>> adjacency_list;

    // Método auxiliar para cargar el grafo desde un archivo
    void load_graph(const std::string& filename);
};

#endif // GRAPH_HPP
