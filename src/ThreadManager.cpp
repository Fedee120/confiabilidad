#include "ThreadManager.hpp"
#include <iostream>
#include <chrono>
#include <random>

ThreadManager::ThreadManager(MonteCarloSimulator& simulator, int num_threads)
    : simulator(simulator), num_threads(num_threads), work_remaining(num_threads), global_processed_count(0) {
    int work_per_thread = simulator.get_num_samples() / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        work_remaining[i] = work_per_thread;
    }
    // Redistribuir el trabajo restante si no es divisible exactamente
    int remaining_work = simulator.get_num_samples() % num_threads;
    for (int i = 0; remaining_work > 0 && i < num_threads; ++i, --remaining_work) {
        work_remaining[i]++;
    }
}

void ThreadManager::run() {
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(&ThreadManager::thread_work, this, i);
    }
}

void ThreadManager::join_all() {
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

std::mt19937 ThreadManager::initialize_rng(int seed) {
    std::random_device rd;
    return std::mt19937(seed + rd());
}

void ThreadManager::thread_work(int thread_id) {
    std::mt19937 rng = initialize_rng(thread_id);

    while (true) {
        int local_work = 0;
        {
            std::lock_guard<std::mutex> guard(work_mutex);
            if (work_remaining[thread_id] > 0) {
                local_work = std::min(static_cast<int>(work_remaining[thread_id]), 1000); // Procesar en lotes de 1000
                work_remaining[thread_id] -= local_work;
            } else {
                // Work stealing: find work from other threads
                for (int i = 0; i < num_threads; ++i) {
                    if (work_remaining[i] > 0) {
                        local_work = std::min(static_cast<int>(work_remaining[i]), 1000); // Procesar en lotes de 1000
                        work_remaining[i] -= local_work;
                        std::cout << "Thread " << thread_id << " is stealing work from thread " << i << std::endl;
                        break;
                    }
                }
            }
        }

        if (local_work == 0) {
            break;
        }

        for (int i = 0; i < local_work; ++i) {
            simulator.perform_simulation(thread_id, rng);

            {
                std::lock_guard<std::mutex> guard(work_mutex);
                global_processed_count++;
                if (global_processed_count % 10000 == 0) {
                    std::cout << "Total processed samples: " << global_processed_count << ". Remaining work: ";
                    for (int j = 0; j < num_threads; ++j) {
                        std::cout << "Thread " << j << ": " << work_remaining[j] << " ";
                    }
                    std::cout << std::endl;
                }
            }
        }
    }
}
