#include "systemVendor.h"

char* SUSPICIOUS_SYS_VENDORS[] = {
        "VMware",
        "VirtualBox",
        "Phoenix",
        "innotek"
};
int SUSPICIOUS_SYS_VENDORS_SIZE = 4;

/**
 * Looks for suspicious system vendors
 * @return If /sys/class/dmi/id/sys_vendor could not be opened: RESULT_UNKNOWN, else if a suspicious vendor was found: RESULT_FAILURE, else: RESULT_SUCCESS
 */
int checkSysVendor(char* resultDescriptionBuffer)
{
    strcpy(resultDescriptionBuffer, "");

    FILE* file;
    file = fopen("/sys/class/dmi/id/sys_vendor", "rb");
    int result = RESULT_SUCCESS;

    if (file == NULL) {
        strcpy(resultDescriptionBuffer, "--> Could not read /sys/class/dmi/id/sys_vendor\n");
        return RESULT_UNKNOWN;
    } else {
        for(int i=0 ; i<SUSPICIOUS_SYS_VENDORS_SIZE ; i++){
            if(checkWordInFile(file, SUSPICIOUS_SYS_VENDORS[i])==RESULT_FAILURE){
                strcat(resultDescriptionBuffer, "--> System vendor is ");
                strcat(resultDescriptionBuffer, (char*) SUSPICIOUS_SYS_VENDORS[i]);
                strcat(resultDescriptionBuffer, ".\n");
                result = RESULT_FAILURE;
            }
        }
        return result;
    }
}