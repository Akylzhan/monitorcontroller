#ifndef MONITORCONTROLLER_H
#define MONITORCONTROLLER_H

#include <physicalmonitorenumerationapi.h>

class MonitorController
{
public:
    MonitorController();
    ~MonitorController();

    int getCurrentBrightness();
    void setBrightness(int newValue);

private:
    LPPHYSICAL_MONITOR physicalMonitor;
};

#endif // MONITORCONTROLLER_H
