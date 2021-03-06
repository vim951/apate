#ifndef APATE_CHROMEHISTORY_H
#define APATE_CHROMEHISTORY_H

#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h> //To read $HOME

#include "../constants.h"
#include "../files.h"
#include "browserHistory.h"

//Declares strptime header
char *strptime(const char *buf, const char *format, struct tm *tm);

//Declares chromeHistory.c headers
int checkChromeLikeHistory(char* name, char* access, char* resultDescriptionBuffer);

#endif //APATE_CHROMEHISTORY_H
