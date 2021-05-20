#include "screenResolution.h"

//https://gs.statcounter.com/screen-resolution-stats/desktop/worldwide
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


/*
    Printing a current screen resolution by using the libX11 (worked only for Unix-like OS)
    https://en.wikipedia.org/wiki/X_Window_System

    Based on:
        https://www.x.org/releases/X11R7.6/doc/libX11/specs/libX11/libX11.html
        http://surfingtroves.blogspot.com/2011/01/how-to-get-screen-resolution-in-linux-c.html
 */
int checkDisplayResolution()
{
    Display *display;
    Window window;
    XWindowAttributes xw_attrs;

    if ((display = XOpenDisplay(NULL)) == NULL) {
        return RESULT_UNKNOWN;
    }

    window = DefaultRootWindow(display);

    XGetWindowAttributes(display, window, &xw_attrs);

    int width   = xw_attrs.width;
    int height  = xw_attrs.height;

    XCloseDisplay(display);

    for (int i=0 ; i<RESOLUTION_LIST_SIZE ; i++){
        if(RESOLUTION_LIST[i][0]==width && RESOLUTION_LIST[i][1]==height){
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}