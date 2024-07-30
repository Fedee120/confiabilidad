#include "graph.hpp"
#include "GraphLoader.hpp"
#include <fstream>
#include <random>
#include <stack>
#include <iostream>

Graph::Graph(const std::string& filename) {
    std::cout << "Loading graph from file: " << filename << std::endl;
    *this = GraphLoader::loadGraphFromCSV(filename);
    std::cout << "Graph loaded successfully." << std::endl;
}

void Graph::load_graph(const std::string& filename) {
    *this = GraphLoader::loadGraphFromCSV(filename);
}

bool Graph::is_connected() const {
    std::unordered_map<int, bool> visited;
    for (const auto& node : adjacency_list) {
        visited[node.first] = false;
    }

    std::stack<int> stack;
    int start_node = adjacency_list.begin()->first;
    stack.push(start_node);
    visited[start_node] = true;
    size_t visited_count = 1;

    //std::cout << "Starting DFS from node: " << start_node << std::endl;

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        //std::cout << "Visiting node: " << node << std::endl;

        for (const auto& neighbor : adjacency_list.at(node)) {
            if (!visited[neighbor.first]) {
                stack.push(neighbor.first);
                visited[neighbor.first] = true;
                visited_count++;
                //std::cout << "Pushing neighbor: " << neighbor.first << " onto the stack" << std::endl;
            }
        }
    }

    //std::cout << "Visited " << visited_count << " out of " << adjacency_list.size() << " nodes" << std::endl;
    return visited_count == adjacency_list.size();
}

Graph Graph::sample_graph() const {
    Graph sampled_graph;
    sampled_graph.adjacency_list = this->adjacency_list;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (auto& [node, neighbors] : sampled_graph.adjacency_list) {
        for (auto it = neighbors.begin(); it != neighbors.end();) {
            std::uniform_real_distribution<> dis(0.0, 1.0);
            if (dis(gen) < it->second) {  // Arista falla y se elimina
                it = neighbors.erase(it);
            } else {
                ++it;
            }
        }
    }

    int edge_count = 0;
    for (const auto& [node, neighbors] : sampled_graph.adjacency_list) {
        edge_count += neighbors.size();
    }
    //std::cout << "Sampled graph with " << edge_count / 2 << " edges" << std::endl;

    return sampled_graph;
}



void Graph::set_adjacency_list(const std::unordered_map<int, std::vector<std::pair<int, double>>>& new_adjacency_list) {
    adjacency_list = new_adjacency_list;
}

const std::unordered_map<int, std::vector<std::pair<int, double>>>& Graph::get_adjacency_list() const {
    return adjacency_list;
}

void Graph::add_edge(int node1, int node2, double probability) {
    adjacency_list[node1].emplace_back(node2, probability);
    adjacency_list[node2].emplace_back(node1, probability); // Asegurar que se añade en ambas direcciones
    //std::cout << "Added edge: " << node1 << " <-> " << node2 << " with probability " << probability << std::endl;
}
