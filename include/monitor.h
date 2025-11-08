#ifndef MONITOR_H
#define MONITOR_H

#include <string>

class SystemMonitor {
private:
    long prevIdle = 0;
    long prevTotal = 0;

public:
    float getCPUUsage();
    float getMemoryUsage();
    int getProcessCount();
};

#endif