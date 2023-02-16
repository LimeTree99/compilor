/*! \file dfa.h
 \brief For creating ad traversing DFA structures.
*/

#include "string.h"
#include <stdio.h>


#define CHARSET_SIZE 255

struct Dfa{
    int *grid;
    char **node_lex;  //if '\0' then not a final node (panic mode)
    int num_nodes;
    int max_nodes;
}Dfa;

struct Symbol{
    char *token;
    char *lexeme;
}Symbol;


struct Dfa *dfa_new(int max_nodes);
struct Symbol next_key(struct Dfa *dfa, char *start);
void set_node(struct Dfa *dfa, int node, char *final, int links[], int links_v);