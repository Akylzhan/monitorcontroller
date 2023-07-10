#include "caffeine.h"

#include <Windows.h>
#include <winbase.h>

Caffeine::Caffeine() {}

Caffeine::~Caffeine()
{
    stopDrinking();
}

void Caffeine::startDrinking()
{
    isDrinking = true;

    if (keepDisplayOn) {
        SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);
    } else {
        SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED);
    }
}

void Caffeine::stopDrinking()
{
    isDrinking = false;
    SetThreadExecutionState(ES_CONTINUOUS);
}
