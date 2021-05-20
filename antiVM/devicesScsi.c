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
int checkScsiDevices()
{
    FILE* file;
    file = fopen("/proc/scsi/scsi", "rb");

    if (file == NULL) {
        return RESULT_UNKNOWN;
    } else {
        for(int i=0 ; i<SUSPICIOUS_SCSI_DEVICES_SIZE ; i++){
            if(checkWordInFile(file, SUSPICIOUS_SCSI_DEVICES[i])==RESULT_FAILURE){
                return RESULT_FAILURE;
            }
        }
        return RESULT_SUCCESS;
    }
}