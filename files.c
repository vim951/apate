#include "files.h"

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

void readFileLine(char* filename, int lineNumber, char* buffer){

    FILE* file;
    file = fopen(filename, "rb");

    const int tempSize = 1024;
    char temp[tempSize];

    if (file == NULL) {
        return;
    } else {
        int i=0;
        while(fgets(temp, tempSize, file) != NULL) {
            if(i==lineNumber){
                strcpy(buffer, temp);
                break;
            }
            i++;
        }
        fclose(file);
    }
}