#ifndef APATE_CHROMEHISTORY_H
#define APATE_CHROMEHISTORY_H

#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h> //To read $HOME

#include "../constants.h"
#include "../files.h"

//Declares strptime header
char *strptime(const char *buf, const char *format, struct tm *tm);

//Declares chromeHistory.c headers
int checkChromeHistory();

#endif //APATE_CHROMEHISTORY_H
