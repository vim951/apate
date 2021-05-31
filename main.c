#include "main.h"


int paramVerbose = 0;
int paramCompact = 0;


void parseParameters(int argc, char *argv[]){
    int opt;
    while ((opt = getopt(argc, argv, "vc")) != -1) {
        switch (opt) {
            case 'v': paramVerbose = 1; break;
            case 'c': paramCompact = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-vc]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}


int main(int argc, char *argv[]) {

    parseParameters(argc, argv);

    char resultDescriptionBuffer[8192];
    strcpy(resultDescriptionBuffer, "");

    printTitle();

    printHeader("ANTI-DEBUGGING");
    debugmenotInit();
    printResult("Checks existence of LINES and COLUMNS environment variables.", test_env_detect(), resultDescriptionBuffer);
    printResult("Checks for breakpoint in _dl_debug_state.", test_ldhook_detect(), resultDescriptionBuffer);
    printResult("Compares beginning of the heap to address of own BSS.", test_nearheap_detect(), resultDescriptionBuffer);
    printResult("Checks base address of ELF and shared libraries for hard-coded values used by GDB.", test_noaslr_detect(), resultDescriptionBuffer);
    printResult("Checks whether parent's name is gdb, strace or ltrace.", test_parent_detect(), resultDescriptionBuffer);
    printResult("Tries to debug itself by calling ptrace.", test_ptrace_detect(), resultDescriptionBuffer);
    printResult("Measures distance of vdso and stack.", test_vdso_detect(), resultDescriptionBuffer);

    printHeader("ANTI-VM");
    printResult("Looks for the hypervisor flag in 'cpuinfo'.", checkHypervisorFlag(resultDescriptionBuffer), resultDescriptionBuffer);
    printResult("Inspects currently loaded modules.", checkLoadedModulesFromLSMOD(resultDescriptionBuffer), resultDescriptionBuffer);
    printResult("Looks for suspicious MAC addresses.", checkMacAddresses(resultDescriptionBuffer), resultDescriptionBuffer);
    printResult("Looks for suspicious SCSI devices.", checkScsiDevices(resultDescriptionBuffer), resultDescriptionBuffer);
    printResult("Looks for suspicious bios vendor.", checkBiosVendor(resultDescriptionBuffer), resultDescriptionBuffer);
    printResult("Looks for suspicious board vendor.", checkBoardVendor(resultDescriptionBuffer), resultDescriptionBuffer);
    printResult("Looks for suspicious product name.", checkProductName(), resultDescriptionBuffer);
    printResult("Looks for suspicious system vendors.", checkSysVendor(), resultDescriptionBuffer);
    printResult("Scans the content of '/usr/bin' for known VM names.", checkUserNames(), resultDescriptionBuffer);
    printResult("Checks the screen resolution.", checkDisplayResolution(), resultDescriptionBuffer);
    printResult("Checks if the file system is bigger than 120GB.", checkFileSystemSpace(), resultDescriptionBuffer);
    printResult("Checks if the system has at least 4GB of RAM.", checkRamSize(), resultDescriptionBuffer);

    printHeader("ANTI-FAKE");
    printResult("Inspects browsers histories", checkBrowserHistory(), resultDescriptionBuffer);
    printResult("Checks that the system has been running for at least 30 minutes", checkUpTime(), resultDescriptionBuffer);

    return 0;
}
