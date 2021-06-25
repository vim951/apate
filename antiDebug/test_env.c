#define _DEFAULT_SOURCE

#include "test_env.h"

int test_env_detect(char* resultDescriptionBuffer)
{
    strcpy(resultDescriptionBuffer, "");
    int result = RESULT_SUCCESS;

    if (getenv("LINES")){
        strcat(resultDescriptionBuffer, "--> Detected 'LINES' variable in the environment.\n");
        result = RESULT_FAILURE;
    }

    if (getenv("COLUMNS")){
        strcat(resultDescriptionBuffer, "--> Detected 'COLUMNS' variable in the environment.\n");
        result = RESULT_FAILURE;
    }

    return result;
}
