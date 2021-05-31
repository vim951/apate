#include "ramSize.h"
#include "../constants.h"
#include <sys/sysinfo.h>

int checkRamSize(char* resultDescriptionBuffer)
{
    strcpy(resultDescriptionBuffer, "");

    struct sysinfo info;

    if (sysinfo(&info) < 0){
        strcat(resultDescriptionBuffer, "--> Could not get memory information via sys/sysinfo.h\n");
        return RESULT_UNKNOWN;
    }

    char tmp[10];
    strcat(resultDescriptionBuffer, "--> Memory is very small (only ");
    snprintf(tmp, 10, "%lu", (info.totalram * info.mem_unit / 1000000000));
    strcat(resultDescriptionBuffer, tmp);
    strcat(resultDescriptionBuffer, "GB).\n");

    return (info.totalram * info.mem_unit / 1000000000) >= 4 ? RESULT_SUCCESS : RESULT_FAILURE;
}