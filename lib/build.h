/*! \file build.h
 \brief Defines static parts of the compilor.
*/

#include "dfa.h"

#define NUM_KEYWORDS 16


char *keywords[NUM_KEYWORDS] = {
    "if", "then", "else", "fi", "while", 
    "do", "od", "not", "and", "or", 
    "def", "fed", "return", "int", "double", 
    "print"};
    