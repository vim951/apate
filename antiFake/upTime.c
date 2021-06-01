#include "upTime.h"

int checkUpTime(char* resultDescriptionBuffer){

    strcpy(resultDescriptionBuffer, "");

    struct sysinfo info;

    if (sysinfo(&info) < 0){
        strcat(resultDescriptionBuffer, "--> Could not get up time via sys/sysinfo.h\n");
        return RESULT_UNKNOWN;
    }

    char tmp[128];
    snprintf(tmp, 128, "--> System has been running for %lumin", (info.uptime / 60));
    strcat(resultDescriptionBuffer, tmp);

    return (info.uptime / 60) < MIN_UPTIME_MINUTES ? RESULT_FAILURE : RESULT_SUCCESS;
}