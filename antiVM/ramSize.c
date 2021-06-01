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

    char tmp[128];
    snprintf(tmp, 128, "--> Memory is only %luGB\n", (info.totalram * info.mem_unit / 1000000000));
    strcat(resultDescriptionBuffer, tmp);

    return (info.totalram * info.mem_unit / 1000000000) >= 4 ? RESULT_SUCCESS : RESULT_FAILURE;
}