#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "../constants.h"
#include "debugmenot.h"
#include "test_env.h"

char test_env_detect()
{
    if (getenv("LINES") || getenv("COLUMNS"))
        return RESULT_FAILURE; /* Debatable */
    else
        return RESULT_SUCCESS;
}
