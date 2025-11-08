#include "monitor.h"
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <algorithm>
#include <limits>

using namespace std;

float SystemMonitor::getCPUUsage() {
    ifstream file("/proc/stat");
    string line;
    getline(file, line);
    file.close();

    istringstream iss(line);
    string cpu;
    long user, nice, system, idle, iowait, irq, softirq, steal;
    iss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    long idleTime = idle + iowait;
    long totalTime = user + nice + system + idle + iowait + irq + softirq + steal;

    long diffIdle = idleTime - prevIdle;
    long diffTotal = totalTime - prevTotal;
    prevIdle = idleTime;
    prevTotal = totalTime;

    return 100.0f * (1.0f - (float)diffIdle / diffTotal);
}

float SystemMonitor::getMemoryUsage() {
    ifstream file("/proc/meminfo");
    string key;
    long memTotal = 0, memAvailable = 0;

    while (file >> key) {
        if (key == "MemTotal:") file >> memTotal;
        else if (key == "MemAvailable:") {
            file >> memAvailable;
            break;
        } else file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    file.close();

    return 100.0f * (1.0f - (float)memAvailable / memTotal);
}

int SystemMonitor::getProcessCount() {
    int count = 0;
    DIR* dir = opendir("/proc");
    if (!dir) return 0;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;
        if (all_of(name.begin(), name.end(), ::isdigit))
            count++;
    }
    closedir(dir);
    return count;
}