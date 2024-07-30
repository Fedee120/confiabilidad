#ifndef THREADMANAGER_HPP
#define THREADMANAGER_HPP

#include "MonteCarloSimulator.hpp"
#include <vector>
#include <thread>
#include <mutex>
#include <random>
#include <atomic>

class ThreadManager {
public:
    ThreadManager(MonteCarloSimulator& simulator, int num_threads);

    // Método que lanza todos los hilos para ejecutar la simulación
    void run();

    // Método que espera a que todos los hilos terminen
    void join_all();

private:
    MonteCarloSimulator& simulator;
    int num_threads;
    std::vector<std::thread> threads;
    std::vector<std::atomic<int>> work_remaining;
    std::mutex work_mutex;
    std::atomic<int> global_processed_count;

    // Método auxiliar para que cada hilo realice la simulación con work stealing
    void thread_work(int thread_id);

    // Método para inicializar un generador de números aleatorios único para cada hilo
    std::mt19937 initialize_rng(int seed);
};

#endif // THREADMANAGER_HPP
