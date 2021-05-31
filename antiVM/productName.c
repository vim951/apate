#include "productName.h"

char* SUSPICIOUS_PRODUCT_NAMES[] = {
        "VMware",
        "VirtualBox",
        "Phoenix",
        "innotek"
};
int SUSPICIOUS_PRODUCT_NAMES_SIZE = 4;

/**
 * Looks for suspicious product names
 * @return If /sys/class/dmi/id/product_name could not be opened: RESULT_UNKNOWN, else if a suspicious name was found: RESULT_FAILURE, else: RESULT_SUCCESS
 */
int checkProductName(char* resultDescriptionBuffer)
{
    strcpy(resultDescriptionBuffer, "");

    FILE* file;
    file = fopen("/sys/class/dmi/id/product_name", "rb");
    int result = RESULT_SUCCESS;

    if (file == NULL) {
        strcat(resultDescriptionBuffer, "--> Could not read /sys/class/dmi/id/product_name\n");
        return RESULT_UNKNOWN;
    } else {
        for(int i=0 ; i<SUSPICIOUS_PRODUCT_NAMES_SIZE ; i++){
            if(checkWordInFile(file, SUSPICIOUS_PRODUCT_NAMES[i])==RESULT_FAILURE){
                strcat(resultDescriptionBuffer, "--> Product is named ");
                strcat(resultDescriptionBuffer, (char*) SUSPICIOUS_PRODUCT_NAMES[i]);
                strcat(resultDescriptionBuffer, ".\n");
                result = RESULT_FAILURE;
            }
        }
        return result;
    }
}