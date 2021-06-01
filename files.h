#ifndef APATE_FILES_H
#define APATE_FILES_H

#include "constants.h"

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>

int cp(const char *to, const char *from);
int checkWordInFile(FILE* file, char* str);
void readFileLine(char* filename, int lineNumber, char* buffer);
int getLastModification(char* path, time_t* lastModification);

#endif //APATE_FILES_H
