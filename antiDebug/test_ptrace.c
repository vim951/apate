#define _DEFAULT_SOURCE
#include <stdio.h>
#include <sys/ptrace.h>

#include "../constants.h"
#include "debugmenot.h"
#include "test_ptrace.h"

int test_ptrace_detect()
{
    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
        return RESULT_FAILURE;
    }

    ptrace(PTRACE_DETACH, 0, NULL, NULL);
    return RESULT_SUCCESS;
}
