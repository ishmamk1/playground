#include "simOS.h"

SimOS::SimOS( int numberOfDisks, unsigned long long amountOfRAM, unsigned long long sizeOfOS )
: totalRAMSize(amountOfRAM) 
{
    // ensure os memory < amount of RAM
    if (sizeOfOS > amountOfRAM) throw std::logic_error("Size of OS exceeds total RAM.");

    // place OS in memory
    MemoryItem os{ 0, sizeOfOS, 1 };
    memory.push_back(os);

    // add os to process table
    ProcessData osProcess;
    osProcess.memoryItem = os;
    osProcess.parentPID = currentProcessPID;
    osProcess.priority = 0;
    osProcess.state = State::RUNNING;

    processTable[availablePIDValue] = osProcess;
    currentProcessPID = availablePIDValue;

    // increment next available PID
    availablePIDValue++;

    // Build disk data types
    disks.resize(numberOfDisks);
}

int SimOS::findAvailableMemory(unsigned long long size) {
    // WORST FIT
    unsigned long long maxHole = 0;
    int maxIndex = -1;

    // iterate through each index and track worst fit
    for (int i = 1; i <= memory.size(); i++) {
        unsigned long long availableSpace;

        if (i == memory.size()) availableSpace = totalRAMSize - (memory[memory.size()-1].itemAddress + memory[memory.size()-1].itemSize);
        else availableSpace = memory[i].itemAddress - (memory[i-1].itemAddress + memory[i-1].itemSize);

        if (availableSpace > maxHole) {
            maxHole = availableSpace;
            maxIndex = i;
        }
    }

    if (maxHole >= size) return maxIndex;
    // return -1 if not available else index
    return -1;
}

bool SimOS::NewProcess( unsigned long long size, int priority )
{
    if (size > totalRAMSize) throw std::logic_error("Size of process exceeds total RAM.");

    // Check if we can allocate size
    int memoryIndex = findAvailableMemory(size);

    if (memoryIndex == -1) return false;

    // Place process in memory
    unsigned long long newMemoryAddress = memory[memoryIndex-1].itemAddress + memory[memoryIndex-1].itemSize;
    MemoryItem process{  newMemoryAddress, size, availablePIDValue };

    memory.insert(memory.begin() + memoryIndex, process);

    // Create process data
    ProcessData processData;
    processData.memoryItem = process;
    processData.parentPID = currentProcessPID;
    processData.priority = priority;
    processData.state = State::READY;

    processTable[availablePIDValue] = processData;

    // add to ready queue or place in CPU
    if (currentProcessPID == 1) {
        currentProcessPID = process.PID;
        processTable[currentProcessPID].state = RUNNING;
    } else if (processTable[currentProcessPID].priority < priority) {
        // push old process back to ready queue
        processTable[currentProcessPID].state = READY; 
        ReadyItem oldProcess{processTable[currentProcessPID].priority, currentProcessPID};
        readyQueue.push(oldProcess);
        
        // give new process the CPU
        currentProcessPID = process.PID;
        processData.state = RUNNING;
    } else {
        ReadyItem newProcess{ priority, process.PID };
        readyQueue.push(newProcess);
    }
    
    availablePIDValue++;

    return true;
}

bool SimOS::SimFork() {
    // do nothing if OS process

    // check memory

    // insert and create child process

    // update process table for child and parent
}

int SimOS::GetCPU() {
    return currentProcessPID;
}