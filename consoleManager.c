//For constants
#include "constants.h"

//To print in the terminal
#include <stdio.h>

//To get string length
#include <string.h>

//To get the terminal width
#include <sys/ioctl.h>
#include <unistd.h>

//To use the abs function
#include <stdlib.h>

//To exploit results
#include "debugmenot/debugmenot.h"

enum Color{BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE, NO_COLOR};

const char* APATE[] = {"  /$$$$$$                       /$$              \n",
                       " /$$__  $$                     | $$              \n",
                       "| $$  \\ $$  /$$$$$$  /$$$$$$  /$$$$$$    /$$$$$$ \n",
                       "| $$$$$$$$ /$$__  $$|____  $$|_  $$_/   /$$__  $$\n",
                       "| $$__  $$| $$  \\ $$ /$$$$$$$  | $$    | $$$$$$$$\n",
                       "| $$  | $$| $$  | $$/$$__  $$  | $$ /$$| $$_____/\n",
                       "| $$  | $$| $$$$$$$/  $$$$$$$  |  $$$$/|  $$$$$$$\n",
                       "|__/  |__/| $$____/ \\_______/   \\___/   \\_______/\n",
                       "          | $$                                   \n",
                       "          | $$                                   \n",
                       "          |__/                                   "};

//Reference: https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
int getTerminalWidth(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void setConsoleColor(int colorID){
    printf("\033[0;3%dm", colorID);
}

void printTitle(){
    setConsoleColor(BLUE);
    printf("\n");
    const int k = 11;
    for (int i=0 ; i<k ; i++){
        printf("%s", APATE[i]);
    }
}

void printHeader(char* sectionName){

    setConsoleColor(YELLOW);

    int terminalWidth = getTerminalWidth();
    int sectionWidth = (int) strlen(sectionName) + 2;
    int leftWidth = (terminalWidth-sectionWidth)/2;
    int rightWidth = terminalWidth - (leftWidth+sectionWidth);

    printf("\n\n\n");

    for (int i=0 ; i<leftWidth; i++){
        printf("=");
    }
    printf(" %s ", sectionName);
    for (int i=0 ; i<rightWidth ; i++){
        printf("=");
    }
    printf("\n\n");

    setConsoleColor(NO_COLOR);
    for (int i=0 ; i<terminalWidth; i++){
        printf("-");
    }
    printf("\n");
}

void printResult(char* testName, int result){

    int terminalWidth = getTerminalWidth();
    int nameLength = (int) strlen(testName);
    int spaceToFill = terminalWidth - nameLength - 11;

    setConsoleColor(NO_COLOR);
    printf("%s", testName);

    for (int i=0 ; i<spaceToFill; i++){
        printf(" ");
    }

    switch (result) {
        case RESULT_NO:
            setConsoleColor(GREEN);
            printf("[ SUCCESS ]\n");
            break;
        case RESULT_YES:
            setConsoleColor(RED);
            printf("[ FAILURE ]\n");
            break;
        default:
            setConsoleColor(NO_COLOR);
            printf("[ UNKNOWN  ]\n");
            break;
    }

    setConsoleColor(NO_COLOR);
    for (int i=0 ; i<terminalWidth; i++){
        printf("-");
    }
}