#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/auxv.h>
#include <string.h>

#include "../constants.h"
#include "debugmenot.h"
#include "test_vdso.h"

int test_vdso_detect()
{
    unsigned long tos;
    unsigned long vdso = getauxval(AT_SYSINFO_EHDR);

    if (this_arch == ARCH_ARM64 || this_arch == ARCH_I386) {
        /* This trick unfortunately does not work on 32bit x86 and ARM64 */
        return RESULT_UNKNOWN;
    }

    if (!vdso) {
        /* Auxiliary vector does not contain vdso entry. Unknown result. */
        return RESULT_UNKNOWN;
    }

    if (!(aslr_active() == RESULT_FAILURE)) {
        /* No ASLR on this machine. Unknown result */
        return RESULT_UNKNOWN;
    }

    if ((unsigned long)&tos > vdso)
        return RESULT_FAILURE;
    else
        return RESULT_SUCCESS;
}

/*
static int cleanup(void)
{
    return 0;
}

int register_test_vdso(struct test_chain *all_tests, unsigned int test_bmp)
{
    struct test_chain *test;

    if (!(test_bmp & (1 << TEST_ID_VDSO)))
        return 0;

    test = test_chain_alloc_new(all_tests);

    if (!test)
        return 1 << TEST_ID_VDSO;

    test->detect = detect;
    test->description = TEST_DESC_VDSO;
    test->name = TEST_NAME_VDSO;
    test->cleanup = cleanup;

    return 0;
}
*/