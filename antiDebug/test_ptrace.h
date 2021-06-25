#ifndef _TEST_PTRACE_H
#define _TEST_PTRACE_H

#include <stdio.h>
#include <sys/ptrace.h>

#include "../constants.h"
#include "debugmenot.h"

int test_ptrace_detect(char* resultDescriptionBuffer);

#endif
