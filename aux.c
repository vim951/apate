#include "aux.h"

int checkWordInFile(FILE* file, char* str){
    const int tempSize = 1024;
    char temp[tempSize];
    rewind(file);
    while(fgets(temp, tempSize, file) != NULL) {
        if((strstr(temp, str)) != NULL) {
            return RESULT_FAILURE;
        }
    }
    return RESULT_SUCCESS;
}