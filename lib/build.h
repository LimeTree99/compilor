/*! \file build.h
 \brief For generating and defining items specific to this lexicon and grammar.
*/

#include "general.h"

#define NUM_KEYWORDS 16

#define NUM_TOKENS 42

//! defines a list of all keywords
char *keywords[NUM_KEYWORDS];

char *token_names[NUM_TOKENS];

enum Token {
    err,
    kw_if, kw_then, kw_else, kw_fi, kw_while, 
    kw_do, kw_od, kw_not, kw_and, kw_or, 
    kw_def, kw_fed, kw_return, kw_int, kw_double, 
    kw_print,
    le, gr, asn,
    eq, le_eq, gr_eq,
    add, sub, mult,
    _div, mod, l_round,
    r_round, l_square, r_square,
    comma, semi_col, end, 
    not_eq, var, _int,
    _double, eps, err_space, dollar
}Token;


