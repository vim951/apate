#include "devicesScsi.h"

char* SUSPICIOUS_SCSI_DEVICES[] = {
        "VMware",
        "VBOX"
};
int SUSPICIOUS_SCSI_DEVICES_SIZE = 2;

/**
 * Looks for suspicious SCSI devices
 * @return If /proc/scsi/scsi could not be opened: RESULT_UNKNOWN, else if a suspicious device was found: RESULT_FAILURE, else: RESULT_SUCCESS
 */
int checkScsiDevices(char* resultDescriptionBuffer)
{

    strcpy(resultDescriptionBuffer, "");

    FILE* file;
    file = fopen("/proc/scsi/scsi", "rb");
    int result = RESULT_SUCCESS;

    if (file == NULL) {
        strcat(resultDescriptionBuffer, "--> Could not read /proc/scsi/scsi\n");
        return RESULT_UNKNOWN;
    } else {
        for(int i=0 ; i<SUSPICIOUS_SCSI_DEVICES_SIZE ; i++){
            if(checkWordInFile(file, SUSPICIOUS_SCSI_DEVICES[i])==RESULT_FAILURE){
                strcat(resultDescriptionBuffer, "--> Found ");
                strcat(resultDescriptionBuffer, (char*) SUSPICIOUS_SCSI_DEVICES[i]);
                strcat(resultDescriptionBuffer, " device.\n");
                result = RESULT_FAILURE;
            }
        }
        return result;
    }
}