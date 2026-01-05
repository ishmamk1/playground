#include <iostream>
#include "simOS.h"

int main() {
    // Create a simulated OS with 2 disks, 1000 bytes of RAM, OS size 100
    SimOS sim(2, 1000, 100);

    std::cout << "=== Initial State ===" << std::endl;
    std::cout << "CPU PID: " << sim.GetCPU() << std::endl;

    // Add a process of size 200, priority 5
    bool added1 = sim.NewProcess(200, 5);
    std::cout << "Added process 1 (size 200, priority 5): " << (added1 ? "YES" : "NO") << std::endl;
    std::cout << "CPU PID: " << sim.GetCPU() << std::endl;

    // Add a process of size 150, priority 3 (should go to ready queue)
    bool added2 = sim.NewProcess(150, 3);
    std::cout << "Added process 2 (size 150, priority 3): " << (added2 ? "YES" : "NO") << std::endl;
    std::cout << "CPU PID: " << sim.GetCPU() << std::endl;

    // Add a process of size 50, priority 10 (should preempt CPU)
    bool added3 = sim.NewProcess(50, 10);
    std::cout << "Added process 3 (size 50, priority 10): " << (added3 ? "YES" : "NO") << std::endl;
    std::cout << "CPU PID: " << sim.GetCPU() << std::endl;

    // Print ready queue PIDs (unordered, just for demo)
}
