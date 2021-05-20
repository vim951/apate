#include "loadedModulesFromLSMOD.h"
#include "../constants.h"
#include "../aux.h"

//To read files
#include <stdio.h>

//https://www.ekkosec.com/blog/2018/3/15/linux-anti-vm-how-does-linux-malware-detect-running-in-a-virtual-machine-
//TODO: move list in a config file
const char* KNOWN_VM_MODULES[]   = {"Vboxsf", "vboxguest",                                            //VirtualBox
                                    "vmw_ballon", "vmxnet", "vmw",                                    //VMware
                                    "xen-vbd", "xen-vnif",                                            //Xen
                                    "virtio_pci", "virtio_net",                                       //Qemu\KVM
                                    "hv_vmbus", "hv_blkvsc", "hv_netvsc", "hv_utils", "hv_storvsc"};  //MS Hyper-V
const int KNOWN_VM_MODULES_SIZE  = 14;

int checkLoadedModulesFromLSMOD(){

    FILE* file;
    file = fopen("/sbin/lsmod", "rb");
    int result, tmp;

    if (file == NULL) {
        return RESULT_UNKNOWN;
    } else {
        result = RESULT_SUCCESS;
        for (int i=0 ; i<KNOWN_VM_MODULES_SIZE ; i++){
            tmp = checkWordInFile(file, (char*) KNOWN_VM_MODULES[i]);
            if(tmp==RESULT_FAILURE){
                result = RESULT_FAILURE;
            }
        }
        fclose (file);
        return result;
    }

}