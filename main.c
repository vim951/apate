#include "consoleManager.h"
#include "debugmenot/debugmenot.h"
#include "debugmenot/test_env.h"
#include "debugmenot/test_nearheap.h"
#include "debugmenot/test_ldhook.h"
#include "debugmenot/test_noaslr.h"

int main() {
    printHeader("ANTI-DEBUGGING");
    debugmenotInit();
    printResult("test_env_detect", test_env_detect());
    printResult("test_ldhook_detect", test_ldhook_detect());
    printResult("test_nearheap_detect", test_nearheap_detect());
    printResult("test_noaslr_detect", test_noaslr_detect());
    return 0;
}
