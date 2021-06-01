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

    char tmp[128];
    snprintf(tmp, 128, "--> File system is only %luGB", (stat.f_bsize * stat.f_blocks / 1000000000));
    strcat(resultDescriptionBuffer, tmp);

    return (stat.f_bsize * stat.f_blocks / 1000000000)>=120 ? RESULT_SUCCESS : RESULT_FAILURE;
}