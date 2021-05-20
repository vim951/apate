#include "biosVendor.h"

char* SUSPICIOUS_BIOS_VENDORS[] = {
        "vmware",
        "vbox",
        "Phoenix",
        "innotek"
};
int SUSPICIOUS_BIOS_VENDORS_SIZE = 4;

/**
 * Looks for suspicious bios vendors
 * @return If /sys/class/dmi/id/bios_vendor could not be opened: RESULT_UNKNOWN, else if a suspicious vendor was found: RESULT_FAILURE, else: RESULT_SUCCESS
 */
int checkBiosVendor()
{
    FILE* file;
    file = fopen("/sys/class/dmi/id/bios_vendor", "rb");

    if (file == NULL) {
        return RESULT_UNKNOWN;
    } else {
        for(int i=0 ; i<SUSPICIOUS_BIOS_VENDORS_SIZE ; i++){
            if(checkWordInFile(file, SUSPICIOUS_BIOS_VENDORS[i])==RESULT_FAILURE){
                return RESULT_FAILURE;
            }
        }
        return RESULT_SUCCESS;
    }
}