#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/auxv.h>

#include "../constants.h"
#include "debugmenot.h"


unsigned int this_arch = UINT_MAX;

const char *arch_strings[] = {
    [ARCH_AMD64] = "x86_64",
    [ARCH_I386]  = "i686",
    [ARCH_ARM64] = "aarch64",
    [ARCH_ARMV7] = "v7l",
};

int aslr_active(void)
{
    char aslr_state[2] = { 0 };
    int res = 0;
    FILE *fp = fopen("/proc/sys/kernel/randomize_va_space", "r");

    if (!fp)
        return RESULT_UNKNOWN;

    if (fread((void *)aslr_state, 1, sizeof(aslr_state) - 1, fp) != sizeof(aslr_state) - 1) {
        fclose(fp);
        return RESULT_UNKNOWN;
    }

    if (aslr_state[0] != '0')
        res = RESULT_FAILURE;
    else
        res = RESULT_SUCCESS;

    fclose(fp);
    return res;
}


int debugmenotInit(){
    for (unsigned int i = 0; i < sizeof(arch_strings) / sizeof(arch_strings[0]); i++) {
        if (!strcmp((const char *)getauxval(AT_PLATFORM), arch_strings[i]))
            this_arch = i;
    }
}
