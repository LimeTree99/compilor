#include "build.h"

char *keywords[NUM_KEYWORDS] = {
    "if", "then", "else", "fi", "while", 
    "do", "od", "not", "and", "or", 
    "def", "fed", "return", "int", "double", 
    "print"};

char *token_names[] = {
    "\0","le","gr","asn",
    "eq","le_eq","gr_eq","add",
    "sub","mult","div","mod",
    "l_round","r_round","l_square","r_square",
    "comma","semi_col","end","not_eq",
    "var","int","double","double",
    "\0","\0","double"};

enum token {
    le, gr, asn,
    eq, le_eq, gr_eq,
    add, sub, mult,
    _div, mod, l_round,
    r_round, l_square, r_square,
    comma, semi_col, end, 
    not_eq, var, _int,
    _double
};