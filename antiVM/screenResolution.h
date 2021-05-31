#ifndef APATE_SCREENRESOLUTION_H
#define APATE_SCREENRESOLUTION_H

#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <string.h>

#include "../constants.h"

#define RESOLUTION_LIST_SIZE 9

int checkDisplayResolution(char* resultDescriptionBuffer);

#endif //APATE_SCREENRESOLUTION_H
