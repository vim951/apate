cmake_minimum_required(VERSION 3.19)
project(apate C)

set(CMAKE_C_STANDARD 11)

add_executable(
        apate

        main.c main.h
        files.c files.h
        consoleManager.c consoleManager.h

        constants.h

        antiDebug/debugmenot.c antiDebug/debugmenot.h
        antiDebug/test_env.c antiDebug/test_env.h
        antiDebug/test_ldhook.c antiDebug/test_ldhook.h
        antiDebug/test_nearheap.c antiDebug/test_nearheap.h
        antiDebug/test_noaslr.c antiDebug/test_noaslr.h
        antiDebug/test_parent.c antiDebug/test_parent.h
        antiDebug/test_ptrace.c antiDebug/test_ptrace.h
        antiDebug/test_vdso.c antiDebug/test_vdso.h

        antiVM/hypervisorFlag.c antiVM/hypervisorFlag.h
        antiVM/fileSystemSpace.c antiVM/fileSystemSpace.h
        antiVM/macAddress.c antiVM/macAddress.h
        antiVM/ramSize.c antiVM/ramSize.h
        antiVM/loadedModulesFromLSMOD.c antiVM/loadedModulesFromLSMOD.h
        antiVM/screenResolution.c antiVM/screenResolution.h
        antiVM/userNames.c antiVM/userNames.h
        antiVM/devicesScsi.c antiVM/devicesScsi.h
        antiVM/biosVendor.c antiVM/biosVendor.h
        antiVM/productName.c antiVM/productName.h
        antiVM/systemVendor.c antiVM/systemVendor.h
        antiVM/boardVendor.c antiVM/boardVendor.h
        antiVM/systemAge.c antiVM/systemAge.h

        antiFake/firefoxHistory.c antiFake/firefoxHistory.h
        antiFake/chromeHistory.c antiFake/chromeHistory.h
        antiFake/browserHistory.c antiFake/browserHistory.h
        antiFake/upTime.c antiFake/upTime.h

)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
target_link_libraries(apate LINK_PUBLIC ${X11_LIBRARIES} sqlite3)