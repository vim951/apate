#define _DEFAULT_SOURCE

#include "test_env.h"

char test_env_detect()
{
    if (getenv("LINES") || getenv("COLUMNS"))
        return RESULT_FAILURE; /* Debatable */
    else
        return RESULT_SUCCESS;
}