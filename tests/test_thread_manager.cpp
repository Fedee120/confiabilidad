#include "ThreadManager.hpp"
#include "GraphLoader.hpp"
#include <iostream>
#include <cassert>
#include <chrono>
#include <cmath>

void test_thread_manager() {
    std::cout << "Starting Thread Manager Test" << std::endl;
    Graph g = GraphLoader::loadGraphFromCSV("data/54-nodes.csv");

    // Verificar que el grafo original es conexo
    bool original_connected = g.is_connected();
    std::cout << "Original graph is_connected: " << original_connected << std::endl;
    assert(original_connected == true);

    int num_samples = 1000000;
    int num_threads = 8;
    MonteCarloSimulator simulator(g, num_samples, num_threads);
    ThreadManager manager(simulator, num_threads);

    // Medir tiempo de ejecución
    auto start_time = std::chrono::high_resolution_clock::now();
    
    manager.run();
    manager.join_all();

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    double reliability = simulator.calculate_reliability();
    std::cout << "Calculated reliability: " << reliability << std::endl;

    // Estimar confiabilidad y calcular el intervalo de confianza
    auto [_, p_hat, variance, confidence_interval] = simulator.estimateReliabilityWithConfidenceInterval(0.95);

    std::cout << "Chebyshev confidence interval: [" << confidence_interval.first << ", " << confidence_interval.second << "]" << std::endl;

    assert(reliability >= 0.0 && reliability <= 1.0);
    std::cout << "Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;
    std::cout << "Thread Manager Test passed!" << std::endl;
}

int main() {
    test_thread_manager();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
