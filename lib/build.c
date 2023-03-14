#include "build.h"

char *keywords[NUM_KEYWORDS] = {
    "if", "then", "else", "fi", "while", 
    "do", "od", "not", "and", "or", 
    "def", "fed", "return", "int", "double", 
    "print"};

char *token_names[] = {
    "le","gr","asn",
    "eq","le_eq","gr_eq",
    "add","sub","mult",
    "div","mod","l_round",
    "r_round","l_square","r_square",
    "comma","semi_col","end",
    "not_eq","var","int",
    "double",
    "kw-if", "kw-then", "kw-else", "kw-fi", "kw-while", 
    "kw-do", "kw-od", "kw-not", "kw-and", "kw-or", 
    "kw-def", "kw-fed", "kw-return", "kw-int", "kw-double", 
    "kw-print"
};

enum token {
    le, gr, asn,
    eq, le_eq, gr_eq,
    add, sub, mult,
    _div, mod, l_round,
    r_round, l_square, r_square,
    comma, semi_col, end, 
    not_eq, var, _int,
    _double,
    kw_if, kw_then, kw_else, kw_fi, kw_while, 
    kw_do, kw_od, kw_not, kw_and, kw_or, 
    kw_def, kw_fed, kw_return, kw_int, kw_double, 
    kw_print
};