#include "GraphLoader.hpp"
#include "MonteCarloSimulator.hpp"
#include "ThreadManager.hpp"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <cmath>

double calculate_mean(const std::vector<double>& data) {
    double sum = 0.0;
    for (double value : data) {
        sum += value;
    }
    return sum / data.size();
}

double calculate_stddev(const std::vector<double>& data, double mean) {
    double sum = 0.0;
    for (double value : data) {
        sum += (value - mean) * (value - mean);
    }
    return std::sqrt(sum / data.size());
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <csv_file> <num_samples> <num_threads> <num_experiments>" << std::endl;
        return 1;
    }

    std::string csv_file = argv[1];
    int num_samples = std::atoi(argv[2]);
    int num_threads = std::atoi(argv[3]);
    int num_experiments = std::atoi(argv[4]);

    if (num_samples <= 0 || num_threads <= 0 || num_experiments <= 0) {
        std::cerr << "num_samples, num_threads, and num_experiments must be positive integers." << std::endl;
        return 1;
    }

    std::cout << "----------------------------" << std::endl;
    std::cout << "Arguments: " << std::endl;
    std::cout << " - CSV file: " << csv_file << std::endl;
    std::cout << " - Number of samples: " << num_samples << std::endl;
    std::cout << " - Number of threads: " << num_threads << std::endl;
    std::cout << " - Number of experiments: " << num_experiments << std::endl;
    std::cout << "----------------------------" << std::endl;

    Graph g = GraphLoader::loadGraphFromCSV(csv_file);

    if (!g.is_connected()) {
        std::cerr << " -- The graph is not connected." << std::endl;
        return 1;
    }

    std::vector<double> reliabilities;
    std::vector<double> elapsed_times;

    for (int i = 0; i < num_experiments; ++i) {
        MonteCarloSimulator simulator(g, num_samples, num_threads);
        ThreadManager manager(simulator, num_threads);
        auto start_time = std::chrono::high_resolution_clock::now();

        manager.run();
        manager.join_all();

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end_time - start_time;

        double reliability = simulator.calculate_reliability();
        reliabilities.push_back(reliability);
        elapsed_times.push_back(elapsed_time.count());

        std::cout << "Experiment " << (i + 1) << " - Calculated reliability: " << reliability << std::endl;
    }

    double mean_reliability = calculate_mean(reliabilities);
    double stddev_reliability = calculate_stddev(reliabilities, mean_reliability);

    double mean_elapsed_time = calculate_mean(elapsed_times);
    double stddev_elapsed_time = calculate_stddev(elapsed_times, mean_elapsed_time);

    std::cout << "Mean reliability: " << mean_reliability << std::endl;
    std::cout << "Standard deviation of reliability: " << stddev_reliability << std::endl;
    std::cout << "Mean elapsed time: " << mean_elapsed_time << " seconds" << std::endl;
    std::cout << "Standard deviation of elapsed time: " << stddev_elapsed_time << " seconds" << std::endl;

    return 0;
}
