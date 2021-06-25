#define _DEFAULT_SOURCE
#include <stdio.h>
#include <sys/auxv.h>
#include <unistd.h>
#include <stdlib.h>

#include "../constants.h"
#include "debugmenot.h"
#include "test_nearheap.h"

int test_nearheap_detect(void)
{
    /* GDB relocates the heap to the end of the bss section */
    static unsigned char bss;
    unsigned char *probe = malloc(0x10);

    if (probe - &bss > 0x20000) {
        return RESULT_SUCCESS;
    } else {
        return RESULT_FAILURE;
    }
}
