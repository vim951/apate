#include "main.h"
#include <stdio.h> //For testing purposes only

int main() {

    printTitle();

    printHeader("ANTI-DEBUGGING");
    debugmenotInit();
    printResult("Checks existence of LINES and COLUMNS environment variables.", test_env_detect());
    printResult("Checks for breakpoint in _dl_debug_state.", test_ldhook_detect());
    printResult("Compares beginning of the heap to address of own BSS.", test_nearheap_detect());
    printResult("Checks base address of ELF and shared libraries for hard-coded values used by GDB.", test_noaslr_detect());
    printResult("Checks whether parent's name is gdb, strace or ltrace.", test_parent_detect());
    printResult("Tries to debug itself by calling ptrace.", test_ptrace_detect());
    printResult("Measures distance of vdso and stack.", test_vdso_detect());

    printHeader("ANTI-VM");
    printResult("Checks if the file system is bigger than 120GB.", checkFileSystemSpace());
    printResult("Checks if the system has at least 4GB of RAM.", checkRamSize());
    printResult("Compares MAC addresses with known vendors.", checkMacAddresses());
    printResult("Looks for the hypervisor flag in 'cpuinfo'.", checkHypervisorFlag());
    printResult("Inspect currently loaded modules.", checkLoadedModulesFromLSMOD());

    printHeader("ANTI-FAKE");
    printResult("Inspect firefox history", checkFirefoxHistory());
    printResult("Inspect chrome history", checkChromeHistory());

    return 0;
}
