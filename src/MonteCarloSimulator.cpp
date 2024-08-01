#include "MonteCarloSimulator.hpp"
#include <iostream>
#include <chrono>
#include <cmath>
#include <algorithm>

MonteCarloSimulator::MonteCarloSimulator(const Graph& graph, int num_samples, int num_threads)
    : original_graph(graph), num_samples(num_samples), num_threads(num_threads), samples_processed(0) {
    connectivity_count.resize(num_threads, 0);
}

void MonteCarloSimulator::perform_simulation(int thread_id, std::mt19937& rng) {
    Graph sampled_graph = original_graph.sample_graph(rng);
    if (sampled_graph.is_connected()) {
        connectivity_count[thread_id]++;
    }
}

void MonteCarloSimulator::simulate(int thread_id, std::mt19937& rng) {
    while (true) {
        int current_sample = samples_processed++;
        if (current_sample >= num_samples) {
            break;
        }
        perform_simulation(thread_id, rng);
    }
}

double MonteCarloSimulator::calculate_reliability() const {
    int total_connected = 0;
    for (const auto& count : connectivity_count) {
        total_connected += count;
    }
    return static_cast<double>(total_connected) / num_samples;
}

std::tuple<double, double, double, std::pair<double, double>> MonteCarloSimulator::estimateReliabilityWithConfidenceInterval(double delta) {
    double p_hat = calculate_reliability();
    double variance = p_hat * (1 - p_hat);
    double beta = std::sqrt(1 / delta);

    double term = std::sqrt((beta * beta) / (4 * num_samples * num_samples) + variance / num_samples);
    double lower_bound = std::max(0.0, p_hat + (beta * beta) / (2 * num_samples) - beta * term);
    double upper_bound = std::min(1.0, p_hat + (beta * beta) / (2 * num_samples) + beta * term);

    return std::make_tuple(0.0, p_hat, variance, std::make_pair(lower_bound, upper_bound));
}
