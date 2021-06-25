#ifndef _TEST_ENV_H
#define _TEST_ENV_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/auxv.h>
#include <string.h>

#include "../constants.h"
#include "debugmenot.h"

int test_vdso_detect(char* resultDescriptionBuffer);

#endif
