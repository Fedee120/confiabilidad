#include "MonteCarloSimulator.hpp"
#include "GraphLoader.hpp"
#include <iostream>
#include <cassert>

void test_monte_carlo_simulation() {
    std::cout << "Starting Monte Carlo Simulation Test" << std::endl;
    Graph g = GraphLoader::loadGraphFromCSV("data/54-nodes.csv");

    // Verificar que el grafo original es conexo
    bool original_connected = g.is_connected();
    std::cout << "Original graph is_connected: " << original_connected << std::endl;
    assert(original_connected == true);

    int num_samples = 100000;
    int num_threads = 4;
    MonteCarloSimulator simulator(g, num_samples, num_threads);

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(&MonteCarloSimulator::simulate, &simulator, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    double reliability = simulator.calculate_reliability();
    std::cout << "Calculated reliability: " << reliability << std::endl;

    assert(reliability >= 0.0 && reliability <= 1.0);
    std::cout << "Monte Carlo Simulation Test passed!" << std::endl;
}

int main() {
    test_monte_carlo_simulation();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
