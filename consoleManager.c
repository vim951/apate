//To print in the terminal
#include <stdio.h>

//To get string length
#include <string.h>

//To get the terminal width
#include <sys/ioctl.h>
#include <unistd.h>

enum Color{BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE, NO_COLOR};

//Reference: https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
int getTerminalWidth(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void setConsoleColor(int colorID){
    printf("\033[0;3%dm", colorID);
}

void printHeader(char* sectionName){

    setConsoleColor(YELLOW);

    int terminalWidth = getTerminalWidth();
    int sectionWidth = (int) strlen(sectionName) + 2;
    int leftWidth = (terminalWidth-sectionWidth)/2;
    int rightWidth = terminalWidth - (leftWidth+sectionWidth);

    for (int i=0 ; i<leftWidth; i++){
        printf("=");
    }
    printf(" %s ", sectionName);
    for (int i=0 ; i<rightWidth ; i++){
        printf("=");
    }
    printf("\n");
}

void printResult(char* testName, char result){

    int terminalWidth = getTerminalWidth();
    int nameLength = (int) strlen(testName);
    int spaceToFill = terminalWidth - nameLength - 11;

    setConsoleColor(NO_COLOR);
    printf("%s", testName);

    for (int i=0 ; i<spaceToFill; i++){
        printf(" ");
    }

    if(result){
        setConsoleColor(GREEN);
        printf("[ SUCCESS ]");
    }else{
        setConsoleColor(RED);
        printf("[ FAILURE ]");
    }
}