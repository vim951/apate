#ifndef _GDB_DETECT_H
#define _GDB_DETECT_H

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/auxv.h>

#include "../constants.h"

int debugmenotInit();

#define DEBUG

struct test_chain {
    /* Performs the actual checkFirefoxHistory. Nonzero return means "debugger found" */
    int (*detect)(void);
    /* Cleanup any leftovers for asynchronous tests */
    int (*cleanup)(void);
    /* Human readable description of the checkFirefoxHistory. */
    const char *description;
    /* Short, but UNIQUELY identifying name of the checkFirefoxHistory. */
    const char *name;
    struct test_chain *next_test;
};

int aslr_active(void);

#if ! defined __linux__
#error "Only supported operating system is Linux."
#endif

#define TEST_ID_MAX 32
#if TEST_ID_MAX > 32
#error "TEST_ID_MAX greater than 32 needs fixing up the print_available_tests function."
#endif

#if ! defined __amd64__ && \
    ! defined __arm__ && \
    ! defined __aarch64__ && \
    ! defined __i386__
#error "Compiling for unknown architecture. Only x86(-64) and ARMV[78] are supported."
#endif

#define ARCH_AMD64 0
#define ARCH_I386  1
#define ARCH_ARM64 2
#define ARCH_ARMV7 3

extern const char *arch_strings[];
extern unsigned int this_arch;

#endif
