#include "hypervisorFlag.h"
#include "../constants.h"

//To read files
#include <stdio.h>
#include <string.h>

int checkWordInFile(FILE* file, char *str) {
    const int tempSize = 1024;
    char temp[tempSize];
    while(fgets(temp, tempSize, file) != NULL) {
        if((strstr(temp, str)) != NULL) {
            return RESULT_YES;
        }
    }
    return RESULT_NO;
}

int checkHypervisorFlag(){

    FILE* file;
    file = fopen("/proc/cpuinfo", "rb");

    if (file == NULL) {
        return RESULT_UNK;
    } else {
        int result = checkWordInFile(file, "hypervisor");
        fclose (file);
        return result;
    }
}
