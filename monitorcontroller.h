#ifndef MONITORCONTROLLER_H
#define MONITORCONTROLLER_H

#include <physicalmonitorenumerationapi.h>

class MonitorController
{
public:
    MonitorController();
    ~MonitorController();

    int getCurrentBrightness() const;
    void setBrightness(int newValue);
    bool findPrimaryMonitor();

private:
    LPPHYSICAL_MONITOR physicalMonitor;
};

#endif // MONITORCONTROLLER_H
