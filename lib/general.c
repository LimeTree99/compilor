#include "general.h" 

#define COLOR_RESET  "\x1b[0m"
#define COLOR_RED    "\x1b[31m"
#define COLOR_GREEN  "\x1b[32m"


void error(char *message, ...){
    va_list args;
    va_start(args, message);
    printf(COLOR_RED);
    printf("Compiler Error: "); 
    printf(COLOR_RESET);
    vprintf(message, args);
    printf("\n");
    exit(1);
}