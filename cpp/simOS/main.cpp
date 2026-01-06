#include <iostream>
#include <cassert>
#include "simOS.h"

void check(const std::string& name, bool condition) {
    std::cout << (condition ? "[PASS] " : "[FAIL] ") << name << "\n";
}

int main() {
    std::cout << "===== Minimal SimFork Tests =====\n";

    // Create OS: 1 disk, 1000 bytes RAM, OS uses 100
    SimOS os(1, 1000, 100);

    /* ---------------------------------------
       TEST 1: OS starts on CPU
    --------------------------------------- */
    check("OS starts running",
          os.GetCPU() == 1);

    /* ---------------------------------------
       TEST 2: Fork from OS fails
    --------------------------------------- */
    bool forkFromOS = os.SimFork();
    check("Fork from OS fails",
          forkFromOS == false);

    /* ---------------------------------------
       TEST 3: Create user process
    --------------------------------------- */
    bool created = os.NewProcess(200, 5);
    check("User process created", created);

    int parentPID = os.GetCPU();
    check("User process on CPU",
          parentPID != 1);

    /* ---------------------------------------
       TEST 4: Fork from user process succeeds
    --------------------------------------- */
    bool forked = os.SimFork();
    check("Fork from user process succeeds",
          forked == true);

    /* ---------------------------------------
       TEST 5: CPU stays with parent after fork
       (child must NOT preempt parent)
    --------------------------------------- */
    check("Parent keeps CPU after fork",
          os.GetCPU() == parentPID);

    /* ---------------------------------------
       TEST 6: Repeated fork does not change CPU
    --------------------------------------- */
    os.SimFork();
    os.SimFork();

    check("CPU still parent after multiple forks",
          os.GetCPU() == parentPID);

    /* ---------------------------------------
       TEST 7: Fork fails when memory exhausted
    --------------------------------------- */
    while (os.NewProcess(200, 1)) {}

    bool forkFail = os.SimFork();
    check("Fork fails when memory full",
          forkFail == false);

    std::cout << "===== Tests Complete =====\n";
    return 0;
}

