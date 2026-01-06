#ifndef SIMOS_H
#define SIMOS_H

#include <string>
#include <queue>
#include <vector>
#include <unordered_map>

enum State{ RUNNING, READY, WAIT, ZOMBIE, ORPHAN };

struct FileReadRequest
{
    int PID;
    std::string fileName{""};
};

struct MemoryItem
{
    unsigned long long itemAddress;
    unsigned long long itemSize;
    int PID; // PID of the process using this chunk of memory
};

struct ProcessData 
{
    MemoryItem memoryItem;
    int parentPID;
    int priority;
    std::vector<int> childrenPID;
    State state;
};

struct Disk
{
    bool busy = false;
    FileReadRequest current;
    std::queue<FileReadRequest> queue;
};

using MemoryUse = std::vector<MemoryItem>;
using ReadyItem = std::pair<int, int>; // <priority, PID>

constexpr int NO_PROCESS{-1};

class SimOS {
    public:
        SimOS( int numberOfDisks, unsigned long long amountOfRAM, unsigned long long sizeOfOS );
        bool NewProcess( unsigned long long size, int priority );
        bool SimFork();
        void SimExit();
        void SimWait();
        void DiskReadRequest( int diskNumber, std::string fileName );
        void DiskJobCompleted( int diskNumber );
        int GetCPU( );
        std::vector<int> GetReadyQueue( );
        MemoryUse GetMemory( );
        FileReadRequest GetDisk( int diskNumber );
        std::queue<FileReadRequest> GetDiskQueue( int diskNumber );

        // Helpers
        int findAvailableMemory(unsigned long long size);

    private:
        int availablePIDValue{ 1 };
        std::vector<Disk> disks;
        std::priority_queue<ReadyItem> readyQueue;
        int currentProcessPID;
        unsigned long long totalRAMSize;
        std::unordered_map<int, ProcessData> processTable;
        MemoryUse memory;
};

#endif
