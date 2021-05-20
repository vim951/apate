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
int checkSysVendor()
{
    FILE* file;
    file = fopen("/sys/class/dmi/id/sys_vendor", "rb");

    if (file == NULL) {
        return RESULT_UNKNOWN;
    } else {
        for(int i=0 ; i<SUSPICIOUS_SYS_VENDORS_SIZE ; i++){
            if(checkWordInFile(file, SUSPICIOUS_SYS_VENDORS[i])==RESULT_FAILURE){
                return RESULT_FAILURE;
            }
        }
        return RESULT_SUCCESS;
    }
}