#include "consoleManager.h"
#include "debugmenot/debugmenot.h"
#include "debugmenot/test_env.h"
#include "debugmenot/test_nearheap.h"
#include "debugmenot/test_ldhook.h"

int main() {
    printHeader("ANTI-DEBUGGING");
    debugmenotInit();
    printResult("test_env_detect", test_env_detect());
    printResult("test_nearheap_detect", (char) test_nearheap_detect());
    printResult("test_ldhook_detect",   (char) test_ldhook_detect());
    return 0;
}
