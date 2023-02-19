/*! \file dfa.h
 \brief For creating ad traversing DFA structures.
*/

#include "string.h"
#include <stdio.h>


#define CHARSET_SIZE 255

struct Dfa{
    int *token_table;
    char **node_lex;  //if '\0' then not a final node (panic mode)
    int num_nodes;
    int max_nodes;
}Dfa;

struct Symbol{
    char *token;    //!Assigned name of symbol
    char *lexeme;   //!Name of found key as is writen in source
}Symbol;

//! Create a new dfa. Use dfa_free() to dereference
/*!
 \param max_nods
 \returns dfa pointer to created dfa
*/
struct Dfa *dfa_new(int max_nodes);

//! generates and fills token table for use in lexing
/*!
 \returns dfa 
*/
struct Dfa *generate_lex1();


bool dfa_free(struct Dfa *dfa);

//! finds the next key in the dfa 
/*!
 \param dfa dfa used to analize characters
 \param buff pointer to the bouble buffer
 \param start first char and will incriment from there until symbol is found
 \returns struct Symbol: containing the next sybol starting with <start>
*/
struct Symbol next_key(struct Dfa *dfa, char *buff, char *start);
void set_node(struct Dfa *dfa, 
              int node, 
              char *lexeme, 
              char *link_char[], 
              int link_num[],
              int links_v);