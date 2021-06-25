#include "screenResolution.h"

/*
 * Based on data from:
 * https://gs.statcounter.com/screen-resolution-stats/desktop/worldwide
 */
#define RESOLUTION_LIST_SIZE 9
const int RESOLUTION_LIST[RESOLUTION_LIST_SIZE][2] = {
        {1366, 768 },
        {1920, 1080},
        {1536, 864 },
        {1440, 900 },
        {1280, 720 },
        {1600, 900 },
        {1280, 800 },
        {1280, 1024},
        {768,  1024}
};


/**
 * Checks if the screen resolution is a common one (otherwise it might be a sign that the screen is virtual)
 * @return RESULT_SUCCESS if it is, RESULT_FAILURE if it is not, and RESULT_UNKNOWN if X11/Xlib.h could not be used
 */
int checkDisplayResolution(char* resultDescriptionBuffer)
{
    strcpy(resultDescriptionBuffer, "");

    Display *display;
    Window window;
    XWindowAttributes xw_attrs;

    if ((display = XOpenDisplay(NULL)) == NULL) {
        strcat(resultDescriptionBuffer, "--> Could not get screen information via X11/Xlib.h\n");
        return RESULT_UNKNOWN;
    }

    window = DefaultRootWindow(display);

    XGetWindowAttributes(display, window, &xw_attrs);

    int width   = xw_attrs.width;
    int height  = xw_attrs.height;

    XCloseDisplay(display);

    char tmp[10];
    strcat(resultDescriptionBuffer, "--> Your screen resolution (");
    snprintf(tmp, 10, "%d", width);
    strcat(resultDescriptionBuffer, tmp);
    strcat(resultDescriptionBuffer, " x ");
    snprintf(tmp, 10, "%d", height);
    strcat(resultDescriptionBuffer, tmp);
    strcat(resultDescriptionBuffer, ") is not common (c.f. https://gs.statcounter.com/screen-resolution-stats/desktop/worldwide).\n");

    for (int i=0 ; i<RESOLUTION_LIST_SIZE ; i++){
        if(RESOLUTION_LIST[i][0]==width && RESOLUTION_LIST[i][1]==height){
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}
