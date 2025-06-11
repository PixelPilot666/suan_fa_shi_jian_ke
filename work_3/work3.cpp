#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>

// Defines the structure for a dynamic task
struct DynamicTask {
    int arrival_time;
    int processing_time;
};

// Helper function: Prints the current loads on all machines
void print_loads(const std::string& prefix, const std::vector<int>& machines) {
    std::cout << prefix;
    for (size_t i = 0; i < machines.size(); ++i) {
        std::cout << "Machine" << i + 1 << "=" << machines[i] << (i == machines.size() - 1 ? "" : ", ");
    }
    std::cout << std::endl;
}

// Helper function: Finds the index of the machine with the minimum current load
int find_min_load_machine_index(const std::vector<int>& machines) {
    return std::min_element(machines.begin(), machines.end()) - machines.begin();
}

// Strategy A: Immediate Greedy
void strategy_a(int m, std::vector<int> static_tasks, const std::vector<DynamicTask>& dynamic_tasks) {
    std::cout << "## Strategy A: Immediate Greedy" << std::endl;
    std::cout << "---" << std::endl;

    // 1. Initialize machines and assign static tasks using LPT (Longest Processing Time)
    std::vector<int> machines(m, 0);
    std::sort(static_tasks.rbegin(), static_tasks.rend()); // Sort tasks in descending order
    for (int task_p : static_tasks) {
        int min_idx = find_min_load_machine_index(machines);
        machines[min_idx] += task_p;
    }
    std::cout << "t=0: Static tasks assigned." << std::endl;
    print_loads("Initial loads: ", machines);
    std::cout << std::endl;

    // 2. Process dynamic tasks as they arrive
    for (const auto& task : dynamic_tasks) {
        std::cout << "Time=" << task.arrival_time << ": Task (a=" << task.arrival_time << ", p=" << task.processing_time << ") has arrived" << std::endl;
        print_loads("Current machine loads: ", machines);

        int machine_idx = find_min_load_machine_index(machines);
        int old_load = machines[machine_idx];
        machines[machine_idx] += task.processing_time;

        std::cout << "Assigned to Machine" << machine_idx + 1 << " (minimum load, "
                  << old_load << " -> " << machines[machine_idx] << ")" << std::endl;
        std::cout << std::endl;
    }

    // 3. Print final results
    std::cout << "---" << std::endl;
    // --- MODIFIED LINE ---
    std::cout << "** Strategy A finished **" << std::endl;
    print_loads("Final loads: ", machines);
    int max_completion_time = *std::max_element(machines.begin(), machines.end());
    std::cout << "Maximum Completion Time (Makespan): " << max_completion_time << std::endl;
}

// Strategy B: Delayed Batch Greedy
void strategy_b(int m, int k, std::vector<int> static_tasks, const std::vector<DynamicTask>& dynamic_tasks) {
    std::cout << "## Strategy B: Delayed Batch Greedy" << std::endl;
    std::cout << "---" << std::endl;

    // 1. Initialize machines (same as Strategy A)
    std::vector<int> machines(m, 0);
    std::sort(static_tasks.rbegin(), static_tasks.rend());
     for (int task_p : static_tasks) {
        int min_idx = find_min_load_machine_index(machines);
        machines[min_idx] += task_p;
    }
    std::cout << "t=0: Static tasks assigned." << std::endl;
    print_loads("Initial loads: ", machines);
    std::cout << std::endl;

    std::vector<DynamicTask> buffer;

    // 2. Process dynamic tasks, buffering them until a condition is met
    for (size_t i = 0; i < dynamic_tasks.size(); ++i) {
        const auto& task = dynamic_tasks[i];
        std::cout << "Time=" << task.arrival_time << ": Task (a=" << task.arrival_time << ", p=" << task.processing_time << ") has arrived" << std::endl;
        buffer.push_back(task);

        // Trigger condition: buffer reaches threshold k OR this is the last dynamic task
        bool is_last_task = (i == dynamic_tasks.size() - 1);
        if (buffer.size() == k || is_last_task) {
            std::cout << "Buffer size reached " << buffer.size() << ", triggering batch dispatch..." << std::endl;
            
            std::sort(buffer.begin(), buffer.end(), [](const DynamicTask& a, const DynamicTask& b) {
                return a.processing_time > b.processing_time;
            });

            std::cout << "Sorted buffer (descending by processing time): ";
            for(const auto& t : buffer) { std::cout << "p=" << t.processing_time << " "; }
            std::cout << std::endl;

            for (const auto& buffered_task : buffer) {
                 print_loads("Current loads: ", machines);
                 int machine_idx = find_min_load_machine_index(machines);
                 int old_load = machines[machine_idx];
                 machines[machine_idx] += buffered_task.processing_time;
                 std::cout << "Assigning task p=" << buffered_task.processing_time 
                           << " to Machine" << machine_idx + 1 << " (" << old_load << " -> " << machines[machine_idx] << ")" << std::endl;
            }
            buffer.clear();
            print_loads("Loads after this batch: ", machines);

        } else {
            std::cout << "Threshold k=" << k << " not reached, task is buffered." << std::endl;
        }
        std::cout << std::endl;
    }

    // 3. Print final results
    std::cout << "---" << std::endl;
    // --- MODIFIED LINE ---
    std::cout << "** Strategy B finished **" << std::endl;
    print_loads("Final loads: ", machines);
    int max_completion_time = *std::max_element(machines.begin(), machines.end());
    std::cout << "Maximum Completion Time (Makespan): " << max_completion_time << std::endl;
}

int main() {
    // --- Input Parameters ---
    int m;
    int k;
    std::vector<int> static_tasks;
    std::vector<DynamicTask> dynamic_tasks;

    std::cout << "# Enter Experiment Parameters" << std::endl;
    
    std::cout << "Enter the number of machines (m): ";
    std::cin >> m;

    std::cout << "Enter the number of static tasks: ";
    int n_static;
    std::cin >> n_static;
    std::cout << "Enter the processing time for each of the " << n_static << " static tasks (separated by spaces): ";
    for(int i = 0; i < n_static; ++i) {
        int p;
        std::cin >> p;
        static_tasks.push_back(p);
    }

    std::cout << "Enter the number of dynamic tasks: ";
    int n_dynamic;
    std::cin >> n_dynamic;
    std::cout << "Enter " << n_dynamic << " dynamic tasks as 'arrival_time processing_time' pairs, one per line:" << std::endl;
    for(int i = 0; i < n_dynamic; ++i) {
        int a, p;
        std::cin >> a >> p;
        dynamic_tasks.push_back({a, p});
    }

    std::cout << "Enter the delay threshold (k): ";
    std::cin >> k;

    std::sort(dynamic_tasks.begin(), dynamic_tasks.end(), [](const DynamicTask& a, const DynamicTask& b) {
        return a.arrival_time < b.arrival_time;
    });

    std::cout << "\n--- Experiment Start ---" << std::endl;

    // --- Run Strategy A ---
    strategy_a(m, static_tasks, dynamic_tasks);
    
    std::cout << "\n\n============================================\n\n";

    // --- Run Strategy B ---
    strategy_b(m, k, static_tasks, dynamic_tasks);

    return 0;
}