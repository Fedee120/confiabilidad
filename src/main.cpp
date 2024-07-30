#include "GraphLoader.hpp"
#include "MonteCarloSimulator.hpp"
#include "ThreadManager.hpp"
#include <iostream>
#include <chrono>
#include <cstdlib>  // Para std::atoi

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <csv_file> <num_samples> <num_threads>" << std::endl;
        return 1;
    }

    std::string csv_file = argv[1];
    int num_samples = std::atoi(argv[2]);
    int num_threads = std::atoi(argv[3]);

    if (num_samples <= 0 || num_threads <= 0) {
        std::cerr << "num_samples and num_threads must be positive integers." << std::endl;
        return 1;
    }

    // Cargar el grafo desde el archivo CSV
    Graph g = GraphLoader::loadGraphFromCSV(csv_file);

    // Verificar que el grafo original es conexo
    if (!g.is_connected()) {
        std::cerr << "The graph is not connected." << std::endl;
        return 1;
    }

    // Configurar el simulador y el manejador de hilos
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
    std::tuple<double, double, double, std::pair<double, double>> result = simulator.estimateReliabilityWithConfidenceInterval(0.95);
    //double p_hat = std::get<1>(result);
    //double variance = std::get<2>(result);
    std::pair<double, double> confidence_interval = std::get<3>(result);

    std::cout << "Chebyshev confidence interval: [" << confidence_interval.first << ", " << confidence_interval.second << "]" << std::endl;
    std::cout << "Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
