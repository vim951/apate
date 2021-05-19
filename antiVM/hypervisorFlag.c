#include "hypervisorFlag.h"
#include "../constants.h"

//To read files
#include <stdio.h>
#include <string.h>

int checkHypervisorFlag(){

    FILE* file;
    file = fopen("/proc/cpuinfo", "rb");

    if (file == NULL) {
        return RESULT_UNK;
    } else {
        fclose (file);
    }
}