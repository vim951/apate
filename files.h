#ifndef APATE_FILES_H
#define APATE_FILES_H

#include "constants.h"

//To read files
#include <stdio.h>
#include <string.h>

int checkWordInFile(FILE* file, char* str);
void readFileLine(char* filename, int lineNumber, char* buffer);

#endif //APATE_FILES_H
