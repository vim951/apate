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
int checkBiosVendor(char* resultDescriptionBuffer)
{

    strcpy(resultDescriptionBuffer, "");

    FILE* file;
    file = fopen("/sys/class/dmi/id/bios_vendor", "rb");
    int result = RESULT_SUCCESS;

    if (file == NULL) {
        strcpy(resultDescriptionBuffer, "--> Could not read /sys/class/dmi/id/bios_vendor");
        return RESULT_UNKNOWN;
    } else {
        for(int i=0 ; i<SUSPICIOUS_BIOS_VENDORS_SIZE ; i++){
            if(checkWordInFile(file, SUSPICIOUS_BIOS_VENDORS[i])==RESULT_FAILURE){
                strcat(resultDescriptionBuffer, "--> Detected ");
                strcat(resultDescriptionBuffer, (char*) SUSPICIOUS_BIOS_VENDORS[i]);
                strcat(resultDescriptionBuffer, " as the bios vendor.\n");
                result = RESULT_FAILURE;
            }
        }
        return result;
    }
}