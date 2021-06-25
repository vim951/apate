#define _DEFAULT_SOURCE

#include "test_ptrace.h"

int test_ptrace_detect(char* resultDescriptionBuffer)
{
    strcpy(resultDescriptionBuffer, "");

    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
        strcat(resultDescriptionBuffer, "--> ptrace call failed.\n");
        return RESULT_FAILURE;
    }

    ptrace(PTRACE_DETACH, 0, NULL, NULL);
    return RESULT_SUCCESS;
}
