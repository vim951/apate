#include "ramSize.h"
#include "../constants.h"
#include <sys/sysinfo.h>

int checkRamSize()
{
    struct sysinfo info;

    if (sysinfo(&info) < 0)
        return RESULT_UNKNOWN;

    return (info.totalram * info.mem_unit / 1000000000) >= 4 ? RESULT_SUCCESS : RESULT_FAILURE;
}