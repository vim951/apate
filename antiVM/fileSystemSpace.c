#include "fileSystemSpace.h"
#include <sys/statvfs.h>
#include "../constants.h"

int checkFileSystemSpace(char* resultDescriptionBuffer){

    strcpy(resultDescriptionBuffer, "");

    struct statvfs stat;

    if (statvfs(".", &stat) != 0) {
        strcat(resultDescriptionBuffer, "--> Could not get file system information via sys/statvfs.h\n");
        return RESULT_UNKNOWN;
    }

    char tmp[10];
    strcat(resultDescriptionBuffer, "--> Your file system is very small (only ");
    snprintf(tmp, 10, "%lu", (stat.f_bsize * stat.f_blocks / 1000000000));
    strcat(resultDescriptionBuffer, tmp);
    strcat(resultDescriptionBuffer, "GB).\n");

    return (stat.f_bsize * stat.f_blocks / 1000000000)>=120 ? RESULT_SUCCESS : RESULT_FAILURE;
}