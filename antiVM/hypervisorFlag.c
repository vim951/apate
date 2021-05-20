#include "hypervisorFlag.h"
#include "../constants.h"
#include "../aux.h"

//To read files
#include <stdio.h>

int checkHypervisorFlag(){

    FILE* file;
    file = fopen("/proc/cpuinfo", "rb");

    if (file == NULL) {
        return RESULT_UNKNOWN;
    } else {
        int result = checkWordInFile(file, "hypervisor");
        fclose (file);
        return result;
    }
}
