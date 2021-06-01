#include <time.h>
#include "systemAge.h"

const char* FILES_CHECK_AGE[]   = {".", "/"};
const int FILES_CHECK_AGE_SIZE  = 2;

int checkSystemAgeCoherence(char* resultDescriptionBuffer){

    char tmp[3][128];
    strcpy(resultDescriptionBuffer, "");

    time_t systemAge, currentDirectory;
    int isOlder;
    int couldReadFiles = RESULT_SUCCESS;
    int result = RESULT_SUCCESS;

    if(getLastModification("/var/log/installer", &systemAge)){
        strcat(resultDescriptionBuffer, "--> Could not read /var/log/installer metadata.\n");
        return RESULT_UNKNOWN;
    }

    for(int i=0 ; i<FILES_CHECK_AGE_SIZE ; i++){
        if(getLastModification(FILES_CHECK_AGE[i], &currentDirectory)){
            snprintf(tmp[0], 128, "--> Could not read %s metadata.\n", FILES_CHECK_AGE[i]);
            strcat(resultDescriptionBuffer, tmp[0]);
            couldReadFiles = RESULT_UNKNOWN;
        }
        isOlder = difftime(currentDirectory, systemAge) >= 0;//should be true
        if(!isOlder){
            strftime(tmp[0], 128, "%d-%m-%Y", localtime(&currentDirectory));
            strftime(tmp[1], 128, "%d-%m-%Y", localtime(&systemAge));
            snprintf(tmp[2], 128, "--> %s is older than /var/log/installer (%s vs %s).\n", FILES_CHECK_AGE[i], tmp[0], tmp[1]);
            strcat(resultDescriptionBuffer, tmp[2]);
            result = RESULT_FAILURE;
        }
    }

    if(result == RESULT_FAILURE){
        return result;
    }else if(couldReadFiles == RESULT_UNKNOWN){
        return RESULT_UNKNOWN;
    }else{
        return RESULT_SUCCESS;
    }
}