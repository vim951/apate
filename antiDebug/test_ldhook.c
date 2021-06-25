#define _DEFAULT_SOURCE

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

int test_ldhook_detect(char* resultDescriptionBuffer)
{
    strcpy(resultDescriptionBuffer, "");

    if (memcmp((void *)*(&_r_debug + 2), arch_ret_ldhook[this_arch],
               arch_ret_len_ldhook[this_arch]))
        return RESULT_FAILURE;
    else
        return RESULT_SUCCESS;
}
