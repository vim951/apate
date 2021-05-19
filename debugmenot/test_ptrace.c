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

/*
static int cleanup(void)
{
    return 0;
}

int register_test_ptrace(struct test_chain *all_tests, unsigned int test_bmp)
{
    struct test_chain *test;

    if (!(test_bmp & (1 << TEST_ID_PTRACE)))
        return 0;

    test = test_chain_alloc_new(all_tests);

    if (!test)
        return 1 << TEST_ID_PTRACE;

    test->detect = detect;
    test->description = TEST_DESC_PTRACE;
    test->name = TEST_NAME_PTRACE;
    test->cleanup = cleanup;

    return 0;
}
*/