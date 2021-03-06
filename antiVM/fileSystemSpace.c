#include "fileSystemSpace.h"
#include <sys/statvfs.h>
#include "../constants.h"

/**
 * Check if the file system is large enough to be the one of a real computer (i.e. >= 120GB)
 * @return RESULT_SUCCESS if it is, RESULT_FAILURE if it is not, and RESULT_UNKNOWN if sys/statvfs.h could not be used
 */
int checkFileSystemSpace(char* resultDescriptionBuffer){

    strcpy(resultDescriptionBuffer, "");

    struct statvfs stat;

    if (statvfs(".", &stat) != 0) {
        strcat(resultDescriptionBuffer, "--> Could not get file system information via sys/statvfs.h\n");
        return RESULT_UNKNOWN;
    }

    char tmp[128];
    snprintf(tmp, 128, "--> File system is only %luGB\n", (stat.f_bsize * stat.f_blocks / 1000000000));
    strcat(resultDescriptionBuffer, tmp);

    return (stat.f_bsize * stat.f_blocks / 1000000000)>=120 ? RESULT_SUCCESS : RESULT_FAILURE;
}