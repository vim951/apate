#include "fileSystemSpace.h"
#include <sys/statvfs.h>
#include "../constants.h"

int checkFileSystemSpace(){

    struct statvfs stat;

    if (statvfs(".", &stat) != 0) {
        return RESULT_UNKNOWN;
    }

    return (stat.f_bsize * stat.f_blocks / 1000000000)>=120 ? RESULT_SUCCESS : RESULT_FAILURE;
}