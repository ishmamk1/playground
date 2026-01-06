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
    if (currentProcessPID == 1) return false;

    // check memory
    unsigned long long processMemorySize = processTable[currentProcessPID].memoryItem.itemSize;
    ProcessData parentProcessData = processTable[currentProcessPID];
    processTable[currentProcessPID].state = State::RUNNING;


    int memoryIndex = findAvailableMemory(processMemorySize);

    if (memoryIndex == -1) return false;

    // Place child process in memory
    unsigned long long newMemoryAddress = memory[memoryIndex-1].itemAddress + memory[memoryIndex-1].itemSize;

    MemoryItem childProcess{  newMemoryAddress, processMemorySize, availablePIDValue };

    memory.insert(memory.begin() + memoryIndex, childProcess);

    ReadyItem readyChildProcessItem{ parentProcessData.priority, availablePIDValue };
    readyQueue.push(readyChildProcessItem);

    // update process table for child and parent
    ProcessData childProcessData;
    childProcessData.memoryItem = childProcess;
    childProcessData.parentPID = currentProcessPID;
    childProcessData.priority = parentProcessData.priority;
    childProcessData.state = State::READY;

    processTable[availablePIDValue] = childProcessData;

    // Update process table for parent
    processTable[currentProcessPID].childrenPID.push_back(childProcess.PID);

    availablePIDValue++;

    return true;
}

void SimOS::SimExit() {
    // return if it is OS process
    if (currentProcessPID == 1) return;

    // Release memory

    // delete decendents


}

void SimOS::SimWait() {
    if (currentProcessPID == 1) return;
}

void SimOS::DiskReadRequest( int diskNumber, std::string fileName ) {
    if (currentProcessPID == 1) return;

    if (diskNumber >= disks.size() || diskNumber < 0) 
        throw std::logic_error("Invalid disk number.");

    // Create file read req
    FileReadRequest fileReq{ currentProcessPID, fileName };

    Disk& disk = disks[diskNumber];

    // place it into disk 
    if (!disk.busy) {
        disk.current = fileReq;
        disk.busy = true;
    } else disk.queue.push(fileReq);

    // update process status to WAITING
    processTable[currentProcessPID].state = WAIT;

    // remove from current cpu 
    if (!readyQueue.empty()) {
        currentProcessPID = readyQueue.top().second;
        readyQueue.pop();
        processTable[currentProcessPID].state = RUNNING;
    }
}

void SimOS::DiskJobCompleted( int diskNumber ) {
    if (diskNumber >= disks.size() || diskNumber < 0) 
        throw std::logic_error("Invalid disk number.");
    
    Disk& disk = disks[diskNumber];

    // GET PID AND add to ready queue / CPU
    int diskPID = disk.current.PID;

    ProcessData& processData = processTable[diskPID];
    ProcessData& currentProcessData = processTable[currentProcessPID];

    if (processData.priority > currentProcessData.priority) {
        // put old process back in ready queue
        // change to ready
        ReadyItem currentProcessItem { currentProcessData.priority, currentProcessData.memoryItem.PID};
        currentProcessData.state = READY;
        readyQueue.push(currentProcessItem);

        // insert new process
        processData.state = RUNNING;
        currentProcessPID = diskPID;

    } else {
        ReadyItem processItem { processData.priority, diskPID};
        processData.state = READY;
        readyQueue.push(processItem);
    }

    // Add next process to disk or set to not busy and clear.
    if (!disk.queue.empty()) {
        FileReadRequest& fileReq = disk.queue.front();
        disk.queue.pop();

        disk.current = fileReq;
        disk.busy = true;
    } else disk.busy = false;

}


int SimOS::GetCPU() {
    return currentProcessPID;
}

std::vector<int> SimOS::GetReadyQueue() {
    std::vector<int> readyQueuePIDs;

    auto copyQueue = readyQueue;

    while (!copyQueue.empty()) {
        int copyProcessPID = copyQueue.top().second;
        readyQueuePIDs.push_back(copyProcessPID);
        copyQueue.pop();
    }

    return readyQueuePIDs;
}

MemoryUse SimOS::GetMemory( ) {
    return memory;
}

FileReadRequest SimOS::GetDisk( int diskNumber ) {
   if (diskNumber >= disks.size() || diskNumber < 0) throw std::logic_error("Invalid disk number.");
   return disks[diskNumber].current;
}

std::queue<FileReadRequest> SimOS::GetDiskQueue( int diskNumber ) {
    if (diskNumber >= disks.size() || diskNumber < 0) throw std::logic_error("Invalid disk number.");
    return disks[diskNumber].queue;
}