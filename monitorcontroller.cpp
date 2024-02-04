#include "monitorcontroller.h"

#include <QDebug>
#include <highlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>
#include <winuser.h>

MonitorController::MonitorController()
{
}

MonitorController::~MonitorController()
{
    DestroyPhysicalMonitor(physicalMonitor->hPhysicalMonitor);
    delete physicalMonitor;
}

int MonitorController::getCurrentBrightness() const
{
    DWORD min, value, max;
    auto success = GetMonitorBrightness(physicalMonitor->hPhysicalMonitor, &min, &value, &max);

    if (!success) {
        qFatal() << "GetMonitorBrightness failed";
    }

    return value;
}

void MonitorController::setBrightness(int newValue)
{
    auto success = SetMonitorBrightness(physicalMonitor->hPhysicalMonitor, newValue);

    if (!success) {
        qFatal() << "SetMonitorBrightness failed";
    }
}

bool MonitorController::findPrimaryMonitor()
{
    // TODO Check if `VESA Monitor Control Command Set` is supported
    HWND windowHandle = FindWindowA(nullptr, nullptr);

    if (windowHandle == nullptr) {
        qFatal() << "FindWindow failed";
        return false;
    }

    HMONITOR monitorHandle = MonitorFromWindow(windowHandle, MONITOR_DEFAULTTOPRIMARY);

    physicalMonitor = static_cast<LPPHYSICAL_MONITOR>(new PHYSICAL_MONITOR);
    auto success = GetPhysicalMonitorsFromHMONITOR(monitorHandle, 1, physicalMonitor);

    if (!success) {
        qFatal() << "could not get physical monitors";
        return false;
    }

    return true;
}
