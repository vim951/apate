#ifndef APATE_FIREFOXHISTORY_H
#define APATE_FIREFOXHISTORY_H

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

//Declares firefoxHistory.c headers
int checkFirefoxHistory(char* resultDescriptionBuffer);

#endif //APATE_FIREFOXHISTORY_H
