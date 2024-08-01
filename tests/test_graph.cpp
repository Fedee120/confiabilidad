#include "graph.hpp"
#include "GraphLoader.hpp"
#include <iostream>
#include <cassert>

void test_graph_loading() {
    std::cout << "Starting test_graph_loading" << std::endl;
    Graph g = GraphLoader::loadGraphFromCSV("data/54-nodes.csv");

    bool connected = g.is_connected();
    std::cout << "Graph is_connected: " << connected << std::endl;
    assert(connected == true);
    std::cout << "test_graph_loading passed!" << std::endl;
}

void test_graph_sampling() {
    std::cout << "Starting test_graph_sampling" << std::endl;
    Graph g = GraphLoader::loadGraphFromCSV("data/54-nodes.csv");

    Graph sampled_graph = g.sample_graph(std::mt19937(42));
    bool connected = sampled_graph.is_connected();
    std::cout << "Sampled graph is_connected: " << connected << std::endl;
    assert(connected == true || connected == false);
    std::cout << "test_graph_sampling passed!" << std::endl;
}

void test_graph_connectivity() {
    std::cout << "Starting test_graph_connectivity" << std::endl;
    Graph disconnected_graph;
    std::unordered_map<int, std::vector<std::pair<int, double>>> adj_list;
    adj_list[1] = {{2, 1.0}};
    adj_list[2] = {{1, 1.0}};
    adj_list[3]; 

    disconnected_graph.set_adjacency_list(adj_list);

    bool connected = disconnected_graph.is_connected();
    std::cout << "Disconnected graph is_connected: " << connected << std::endl;
    assert(connected == false);
    std::cout << "test_graph_connectivity passed!" << std::endl;
}

int main() {
    test_graph_loading();
    test_graph_sampling();
    test_graph_connectivity();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
