#include "GraphLoader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <unordered_set> // Add this line

Graph GraphLoader::loadGraphFromCSV(const std::string& filepath) {
    Graph graph;
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file: " << filepath << std::endl;
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    int edge_count = 0;
    std::unordered_set<int> nodes;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        int node1, node2;
        float reliability;

        // Read the first node
        if (!std::getline(iss, token, ',')) {
            std::cerr << "Error reading node1 from line: " + line << std::endl;
            throw std::runtime_error("Error reading node1 from line: " + line);
        }
        node1 = std::stoi(token);

        // Read the second node
        if (!std::getline(iss, token, ',')) {
            std::cerr << "Error reading node2 from line: " + line << std::endl;
            throw std::runtime_error("Error reading node2 from line: " + line);
        }
        node2 = std::stoi(token);

        // Read the reliability (failure probability)
        if (!std::getline(iss, token, ',')) {
            std::cerr << "Error reading reliability from line: " + line << std::endl;
            throw std::runtime_error("Error reading reliability from line: " + line);
        }
        reliability = std::stof(token); // This is the failure probability

        graph.add_edge(node1, node2, reliability);
        edge_count++;
        nodes.insert(node1);
        nodes.insert(node2);
    }
    std::cout << " - Graph loaded successfully!" << std::endl;
    std::cout << " - Number of nodes: " << nodes.size() << std::endl;
    std::cout << " - Number of edges: " << edge_count << std::endl;
    return graph;
}
