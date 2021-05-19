#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <ifaddrs.h>

#include "macAddress.h"
#include "../constants.h"

#define HWADDR_len 6

//https://www.ekkosec.com/blog/2018/3/15/linux-anti-vm-how-does-linux-malware-detect-running-in-a-virtual-machine-
const char* KNOWN_MAC[]   = {"000569", "00A0B1", "545200", "001307", "0013BE", "00240B", "001C14", "080027", "0003FF", "0242AC"};
const int KNOWN_MAC_SIZE  = 10;

//https://stackoverflow.com/questions/4770985/how-to-check-if-a-string-starts-with-another-string-in-c
int startsWith(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

//https://stackoverflow.com/questions/6767296/how-to-get-local-ip-and-mac-address-c/6767517#6767517
void getMacAddressFromInterface(char *MAC_str, char* src)
{
    struct ifreq ifr;
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, src);
    ioctl(s, SIOCGIFHWADDR, &ifr);
    for (int i=0; i<HWADDR_len; i++)
        sprintf(&MAC_str[i*2],"%02X",((unsigned char*)ifr.ifr_hwaddr.sa_data)[i]);
    MAC_str[12]='\0';
}

//https://gist.github.com/edufelipe/6108057#file-is_wireless-c-L39
int checkMacAddresses()
{

    struct ifaddrs *ifaddr, *ifa;
    char mac[13];

    if (getifaddrs(&ifaddr) == -1) {
        return RESULT_UNKNOWN;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {

        if (ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family != AF_PACKET) continue;

        getMacAddressFromInterface(mac, ifa->ifa_name);
        for (int i=0 ; i<KNOWN_MAC_SIZE ; i++){
            if(startsWith(KNOWN_MAC[i], mac)){
                return RESULT_FAILURE;
            }
        }
    }

    freeifaddrs(ifaddr);
    return RESULT_SUCCESS;
}
