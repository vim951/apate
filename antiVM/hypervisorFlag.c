#include "hypervisorFlag.h"
#include "../constants.h"
#include "../files.h"

//To read files
#include <stdio.h>

int checkHypervisorFlag(char* resultDescriptionBuffer){

    strcpy(resultDescriptionBuffer, "");

    FILE* file;
    file = fopen("/proc/cpuinfo", "rb");

    if (file == NULL) {
        strcat(resultDescriptionBuffer, "--> Could not read /proc/cpuinfo\n");
        return RESULT_UNKNOWN;
    } else {
        int result = checkWordInFile(file, "hypervisor");
        fclose (file);
        if(result==RESULT_FAILURE){
            strcat(resultDescriptionBuffer, "--> Found hypervisor flag in /proc/cpuinfo\n");
        }
        return result;
    }
}
