#ifndef APATE_BROWSERHISTORY_H
#define APATE_BROWSERHISTORY_H

#include "../constants.h"
#include "chromeHistory.h"
#include "firefoxHistory.h"

time_t now, x_days_ago;
struct tm x_days_ago_tm;

int checkBrowserHistory(char* resultDescriptionBuffer);

#endif //APATE_BROWSERHISTORY_H
