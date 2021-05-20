#include "userNames.h"

char* SUSPICIOUS_USR_BIN_FILES[] = {
        "vmware-",
        "vbox",
        "qemu"
};
int SUSPICIOUS_USR_BIN_FILES_SIZE = 3;

/**
 * Scans the content of /usr/bin for known VM names
 * @return If the directory could not be scanned: RESULT_UNKNOWN, else if a suspicious file was found: RESULT_FAILURE, else: RESULT_SUCCESS
 */
int checkUserNames()
{
    DIR* usrBin;
    struct dirent *dir;
    usrBin = opendir("/usr/bin");
    if (usrBin)
    {
        while ((dir = readdir(usrBin)) != NULL)
        {
            for (int i=0 ; i<SUSPICIOUS_USR_BIN_FILES_SIZE ; i++){
                if((strstr(dir->d_name, SUSPICIOUS_USR_BIN_FILES[i])) != NULL) {
                    closedir(usrBin);
                    return RESULT_FAILURE;
                }
            }
        }
        closedir(usrBin);
    }
    return RESULT_SUCCESS;
}
