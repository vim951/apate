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
int checkProductName()
{
    FILE* file;
    file = fopen("/sys/class/dmi/id/product_name", "rb");

    if (file == NULL) {
        return RESULT_UNKNOWN;
    } else {
        for(int i=0 ; i<SUSPICIOUS_PRODUCT_NAMES_SIZE ; i++){
            if(checkWordInFile(file, SUSPICIOUS_PRODUCT_NAMES[i])==RESULT_FAILURE){
                return RESULT_FAILURE;
            }
        }
        return RESULT_SUCCESS;
    }
}