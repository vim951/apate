#ifndef APATE_MAIN_H
#define APATE_MAIN_H


extern int paramVerbose;
extern int paramCompact;


//======================================== EXTERNAL INCLUDES =========================================

#include <unistd.h> //Parameters parsing

//======================================== INTERNAL INCLUDES =========================================

#include "consoleManager.h"

#include "antiDebug//debugmenot.h"
#include "antiDebug/test_env.h"
#include "antiDebug/test_nearheap.h"
#include "antiDebug/test_ldhook.h"
#include "antiDebug/test_noaslr.h"
#include "antiDebug/test_parent.h"
#include "antiDebug/test_ptrace.h"
#include "antiDebug/test_vdso.h"

#include "antiVM/hypervisorFlag.h"
#include "antiVM/fileSystemSpace.h"
#include "antiVM/macAddress.h"
#include "antiVM/ramSize.h"
#include "antiVM/loadedModulesFromLSMOD.h"
#include "antiVM/screenResolution.h"
#include "antiVM/userNames.h"
#include "antiVM/devicesScsi.h"
#include "antiVM/biosVendor.h"
#include "antiVM/productName.h"
#include "antiVM/systemVendor.h"
#include "antiVM/boardVendor.h"

#include "antiFake/browserHistory.h"
#include "antiFake/upTime.h"
#include "antiVM/systemAge.h"

#endif //APATE_MAIN_H
