#include "upTime.h"

int checkUpTime()
{
    struct sysinfo info;

    if (sysinfo(&info) < 0)
        return RESULT_UNKNOWN;

    return (info.uptime / 60) < MIN_UPTIME_MINUTES ? RESULT_FAILURE : RESULT_SUCCESS;
}