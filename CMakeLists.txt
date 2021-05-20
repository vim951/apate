cmake_minimum_required(VERSION 3.19)
project(apate C)

set(CMAKE_C_STANDARD 11)

add_executable(
        apate

        main.c
        main.h
        constants.h

        consoleManager.c
        consoleManager.h

        debugmenot/debugmenot.c debugmenot/debugmenot.h
        debugmenot/test_env.c debugmenot/test_env.h
        debugmenot/test_ldhook.c debugmenot/test_ldhook.h
        debugmenot/test_nearheap.c debugmenot/test_nearheap.h
        debugmenot/test_noaslr.c debugmenot/test_noaslr.h
        debugmenot/test_parent.c debugmenot/test_parent.h
        debugmenot/test_ptrace.c debugmenot/test_ptrace.h
        debugmenot/test_vdso.c debugmenot/test_vdso.h

        antiVM/hypervisorFlag.c antiVM/hypervisorFlag.h
        antiVM/fileSystemSpace.c antiVM/fileSystemSpace.h
        antiVM/macAddress.c antiVM/macAddress.h
        antiVM/ramSize.c antiVM/ramSize.h
        antiVM/loadedModulesFromLSMOD.c antiVM/loadedModulesFromLSMOD.h
        aux.c aux.h)