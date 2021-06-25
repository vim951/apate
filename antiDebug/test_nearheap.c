#define _DEFAULT_SOURCE

#include "test_nearheap.h"

int test_nearheap_detect(char* resultDescriptionBuffer)
{
    strcpy(resultDescriptionBuffer, "");

    /* GDB relocates the heap to the end of the bss section */
    static unsigned char bss;
    unsigned char *probe = malloc(0x10);

    if (probe - &bss > 0x20000) {
        return RESULT_SUCCESS;
    } else {
        char txt[100];
        snprintf(txt, 99, "--> dist = %ld.\n", probe - &bss);
        strcat(resultDescriptionBuffer, txt);
        return RESULT_FAILURE;
    }
}
