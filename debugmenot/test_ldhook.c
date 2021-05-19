#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugmenot.h"
#include "test_ldhook.h"

extern long _r_debug;

static const unsigned char *arch_ret_ldhook[] = {
    [ARCH_AMD64] = (unsigned char *)"\xf3\xc3",           /* rep ret */
    [ARCH_I386]  = (unsigned char *)"\xf3\xc3",           /* rep ret */
    [ARCH_ARM64] = (unsigned char *)"\xc0\x03\x5f\xd6",   /* ret     */
    [ARCH_ARMV7] = (unsigned char *)"\x1e\xff\x2f\xe1",   /* bx lr   */
};

static const size_t arch_ret_len_ldhook[] = {
    [ARCH_AMD64] = 2,
    [ARCH_I386]  = 2,
    [ARCH_ARM64] = 4,
    [ARCH_ARMV7] = 4,
};

int test_ldhook_detect(void)
{
    return memcmp((void *)*(&_r_debug + 2), arch_ret_ldhook[this_arch], arch_ret_len_ldhook[this_arch]);
}
/*
static int cleanup(void)
{
    return 0;
}

int register_test_ldhook(struct test_chain *all_tests, unsigned int test_bmp)
{
    struct test_chain *test;

    if (!(test_bmp & (1 << TEST_ID_LDHOOK)))
        return 0;

    test = test_chain_alloc_new(all_tests);

    if (!test)
        return 1 << TEST_ID_LDHOOK;

    test->detect = detect;
    test->description = TEST_DESC_LDHOOK;
    test->name = TEST_NAME_LDHOOK;
    test->cleanup = cleanup;

    return 0;
}
*/
