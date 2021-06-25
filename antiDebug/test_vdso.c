#define _DEFAULT_SOURCE

#include "test_vdso.h"

int test_vdso_detect(char* resultDescriptionBuffer)
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
