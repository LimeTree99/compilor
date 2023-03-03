/*! \file dfa.h
 \brief For creating and traversing DFA structures.
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

typedef struct Symbol{
    int line_num;   //!< Line that the token appears at
    int char_num;   //!< Location of first char of the token in the current line
    char *token;    //!< Assigned name of symbol
    char *lexeme;   //!< Name of found key as is writen in source
}Symbol;

//! generates and fills token table for use in lexing
/*!
 \returns dfa 
*/
struct Dfa *generate_lex1();


//! Create a new dfa. Use dfa_free() to dereference
/*!
 \param max_nods
 \returns dfa pointer to created dfa
*/
struct Dfa *dfa_new(int max_nodes);


bool dfa_free(struct Dfa *dfa);

//! finds the next key in the dfa 
/*!
 \param dfa dfa used to analize characters
 \param buff pointer to the bouble buffer
 \param start first char and will incriment from there until symbol is found
 \param char_num
 \param error_fh
 \returns struct Symbol: containing the next sybol starting with <start>
*/
Symbol next_key(struct Dfa *dfa, 
                char *buff, 
                char **cursor, 
                int *char_num, 
                FILE *error_fh);


void set_node(struct Dfa *dfa, 
              int node, 
              char *lexeme, 
              char *link_char[], 
              int link_num[],
              int links_v);