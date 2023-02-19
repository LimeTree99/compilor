/*! \file build.h
 \brief Defines static variables of the compilor
*/

#include "dfa.h"

#define NUM_KEYWORDS 16

//! defines a list of all keywords
char *keywords[NUM_KEYWORDS] = {
    "if", "then", "else", "fi", "while", 
    "do", "od", "not", "and", "or", 
    "def", "fed", "return", "int", "double", 
    "print"};
    
