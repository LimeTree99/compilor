#include "build.h"

char *keywords[NUM_KEYWORDS] = {
    "if", "then", "else", "fi", "while", 
    "do", "od", "not", "and", "or", 
    "def", "fed", "return", "int", "double", 
    "print"};

char *token_names[NUM_TOKENS] = {
    "err",
    "kw-if", "kw-then", "kw-else", "kw-fi", "kw-while", 
    "kw-do", "kw-od", "kw-not", "kw-and", "kw-or", 
    "kw-def", "kw-fed", "kw-return", "kw-int", "kw-double", 
    "kw-print",
    "le","gr","asn",
    "eq","le_eq","gr_eq",
    "add","sub","mult",
    "div","mod","l_round",
    "r_round","l_square","r_square",
    "comma","semi_col","end",
    "not_eq","var","int",
    "double"
};

