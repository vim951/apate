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

const char* APATE[] = {"  /$$$$$$                       /$$              ",
                       " /$$__  $$                     | $$              ",
                       "| $$  \\ $$  /$$$$$$  /$$$$$$  /$$$$$$    /$$$$$$ ",
                       "| $$$$$$$$ /$$__  $$|____  $$|_  $$_/   /$$__  $$",
                       "| $$__  $$| $$  \\ $$ /$$$$$$$  | $$    | $$$$$$$$",
                       "| $$  | $$| $$  | $$/$$__  $$  | $$ /$$| $$_____/",
                       "| $$  | $$| $$$$$$$/  $$$$$$$  |  $$$$/|  $$$$$$$",
                       "|__/  |__/| $$____/ \\_______/   \\___/   \\_______/",
                       "          | $$                                   ",
                       "          | $$                                   ",
                       "          |__/                                   "};

int getTerminalWidth(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void setConsoleColor(int colorID){
    printf("\033[0;3%dm", colorID);
}

void surroundText(char* text, char placeholder){
    int terminalWidth = getTerminalWidth();
    int textWidth = (int) strlen(text) + 2;
    int leftWidth = (terminalWidth - textWidth) / 2;
    int rightWidth = terminalWidth - (leftWidth + textWidth);

    for (int i=0 ; i<leftWidth; i++){
        printf("%c", placeholder);
    }
    printf(" %s ", text);
    for (int i=0 ; i<rightWidth ; i++){
        printf("%c", placeholder);
    }
    printf("\n");
}

void printTitle(){
    setConsoleColor(BLUE);
    printf("\n\n");
    for (int i=0 ; i<11 ; i++){
        surroundText(APATE[i], ' ');
    }
}

void printHeader(char* sectionName){

    setConsoleColor(YELLOW);

    printf("\n\n");
    surroundText(sectionName, '=');
    printf("\n");

    setConsoleColor(NO_COLOR);
    for (int i=0 ; i<getTerminalWidth(); i++){
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