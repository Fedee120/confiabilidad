#ifndef MONTECARLOSIMULATOR_HPP
#define MONTECARLOSIMULATOR_HPP

#include "graph.hpp"
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <tuple>
#include <random>

class MonteCarloSimulator {
public:
    MonteCarloSimulator(const Graph& graph, int num_samples, int num_threads);

    // Método que realiza la simulación para un hilo específico
    void simulate(int thread_id, std::mt19937& rng);

    // Método que calcula la confiabilidad de la red después de las simulaciones
    double calculate_reliability() const;

    // Método auxiliar para realizar una única simulación
    void perform_simulation(int thread_id, std::mt19937& rng);

    // Método para obtener el número de muestras
    int get_num_samples() const { return num_samples; }

    // Método para estimar la confiabilidad y calcular el intervalo de confianza
    std::tuple<double, double, double, std::pair<double, double>> estimateReliabilityWithConfidenceInterval(double delta);

private:
    Graph original_graph;
    int num_samples;
    int num_threads;
    std::atomic<int> samples_processed;
    std::vector<int> connectivity_count;
    std::mutex work_mutex;
};

#endif // MONTECARLOSIMULATOR_HPP
