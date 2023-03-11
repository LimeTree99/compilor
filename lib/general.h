/*! \file general.h
 \brief For basic utility.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum{false=0, true=1}bool;

FILE *SYMBOL_FH;   //! Output for the symbol table  
FILE *ERROR_FH;    //! Output for errors

#define BUFF_SIZE 15        //! Buffer size for file input
                            //currently no safeguard if token is longer than BUFF_SIZE



#define COLOR_RESET  "\x1b[0m"
#define COLOR_RED    "\x1b[31m"
#define COLOR_GREEN  "\x1b[32m"


void error(char *message, ...);