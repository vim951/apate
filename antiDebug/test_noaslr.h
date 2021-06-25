#ifndef _TEST_NOASLR_H
#define _TEST_NOASLR_H

#include <stdio.h>
#include <sys/auxv.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <string.h>

#include "../constants.h"
#include "debugmenot.h"

int test_noaslr_detect();

#endif
