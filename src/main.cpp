#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include "monitor.h"

using namespace std;

int main() {
    cout << "======================================" << endl;
    cout << "        Linux System Monitor Tool     " << endl;
    cout << "======================================" << endl;

    SystemMonitor monitor;

    while (true) {
        float cpu = monitor.getCPUUsage();
        float mem = monitor.getMemoryUsage();
        int proc = monitor.getProcessCount();

        cout << fixed << setprecision(2);
        cout << "\rCPU Usage: " << cpu << "% | "
             << "Memory Usage: " << mem << "% | "
             << "Processes: " << proc << flush;

        this_thread::sleep_for(chrono::seconds(2));
    }

    return 0;
}