#define _DEFAULT_SOURCE

#include "test_parent.h"

int test_parent_detect(char* resultDescriptionBuffer)
{

    strcpy(resultDescriptionBuffer, "");

    char link_name[0x100] = { 0 };
    size_t target_max_len = 0x100;
    ssize_t target_real_len = 0;
    int res = 0;
    char *link_target = calloc(target_max_len, sizeof(char));
    if (!link_target) {
        fprintf(stderr, "Out of memory in file __FILE__!");
        return RESULT_UNKNOWN;
    }
    pid_t parent = getppid();

    snprintf(link_name, sizeof(link_name) - 1, "/proc/%u/exe", parent);
    while ((target_real_len = readlink(link_name, link_target, target_max_len))
                                                             == target_max_len) {
        target_max_len *= 2;
        /* BUG: This leaks a chunk of memory of size target_max_len if realloc
         * fails, but I'm willing to take this risk ... */
        link_target = realloc(link_target, target_max_len);
        if (!link_target) {
            fprintf(stderr, "Out of memory in file __FILE__ while growing buf!");
            return 0;
        }
        memset(link_target, '\x00', target_max_len);
    }

    if (!strcmp(basename(link_target), "gdb"))
        res = RESULT_FAILURE;
    if (strstr(link_target, "lldb"))
        res = RESULT_FAILURE;
    if (!strcmp(basename(link_target), "strace"))
        res = RESULT_FAILURE;
    if (!strcmp(basename(link_target), "ltrace"))
        res = RESULT_FAILURE;

    free(link_target);
    return res;
}
