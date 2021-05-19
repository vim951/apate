#include "main.h"
#include <stdio.h> //For testing purposes only

int main() {

    printTitle();

    printHeader("ANTI-DEBUGGING");
    debugmenotInit();
    printResult("Checks existence of LINES and COLUMNS environment variables.", test_env_detect());
    printResult("Checks for breakpoint in _dl_debug_state", test_ldhook_detect());
    printResult("Compares beginning of the heap to address of own BSS.", test_nearheap_detect());
    printResult("Checks base address of ELF and shared libraries for hard-coded values used by GDB.", test_noaslr_detect());
    printResult("Checks whether parent's name is gdb, strace or ltrace.", test_parent_detect());
    printResult("Tries to debug itself by calling ptrace(PTRACE_TRACEME, ...)", test_ptrace_detect());
    printResult("Measures distance of vdso and stack.", test_vdso_detect());

    printHeader("ANTI-VM");
    printResult("Checks the hypervisor flag in /proc/cpuinfo", checkHypervisorFlag());
    printResult("Checks if the file system is bigger than 120GB", checkFileSystemSpace());
    return 0;
}
