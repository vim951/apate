#ifndef APATE_UPTIME_H
#define APATE_UPTIME_H

#include "../constants.h"
#include <sys/sysinfo.h>
#include <string.h>
#include <stdio.h>

#define MIN_UPTIME_MINUTES 30

int checkUpTime(char* resultDescriptionBuffer);

#endif //APATE_UPTIME_H
