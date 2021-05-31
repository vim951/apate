#include "boardVendor.h"

char* SUSPICIOUS_BOARD_VENDORS[] = {
        "VMware",
        "VirtualBox",
        "Phoenix",
        "innotek",
        "Oracle"
};
int SUSPICIOUS_BOARD_VENDORS_SIZE = 5;

/**
 * Looks for suspicious board vendors
 * @return If /sys/class/dmi/id/board_vendor could not be opened: RESULT_UNKNOWN, else if a suspicious vendor was found: RESULT_FAILURE, else: RESULT_SUCCESS
 */
int checkBoardVendor(char* resultDescriptionBuffer)
{

    strcpy(resultDescriptionBuffer, "");

    FILE* file;
    file = fopen("/sys/class/dmi/id/board_vendor", "rb");
    int result = RESULT_SUCCESS;

    if (file == NULL) {
        strcpy(resultDescriptionBuffer, "--> Could not read /sys/class/dmi/id/board_vendor\n");
        return RESULT_UNKNOWN;
    } else {
        for(int i=0 ; i<SUSPICIOUS_BOARD_VENDORS_SIZE ; i++){
            if(checkWordInFile(file, SUSPICIOUS_BOARD_VENDORS[i])==RESULT_FAILURE){
                strcat(resultDescriptionBuffer, "--> Detected ");
                strcat(resultDescriptionBuffer, (char*) SUSPICIOUS_BOARD_VENDORS[i]);
                strcat(resultDescriptionBuffer, " as the board vendor.\n");
                result = RESULT_FAILURE;
            }
        }
        return result;
    }
}