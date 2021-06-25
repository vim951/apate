#include "ramSize.h"
#include "../constants.h"
#include <sys/sysinfo.h>

/**
 * Check if the memory is large enough to be the one of a real computer (i.e. >= 4GB)
 * @return RESULT_SUCCESS if it is, RESULT_FAILURE if it is not, and RESULT_UNKNOWN if sys/sysinfo.h could not be used
 */
int checkRamSize(char* resultDescriptionBuffer)
{
    strcpy(resultDescriptionBuffer, "");

    struct sysinfo info;

    if (sysinfo(&info) < 0){
        strcat(resultDescriptionBuffer, "--> Could not get memory information via sys/sysinfo.h\n");
        return RESULT_UNKNOWN;
    }

    char tmp[128];
    snprintf(tmp, 128, "--> Memory is only %luGB\n", (info.totalram * info.mem_unit / 1000000000));
    strcat(resultDescriptionBuffer, tmp);

    return (info.totalram * info.mem_unit / 1000000000) >= 4 ? RESULT_SUCCESS : RESULT_FAILURE;
}