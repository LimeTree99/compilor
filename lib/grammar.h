#include "dfa.h"


typedef struct Grammar{
    int name;
    struct G_node **roots;  //!< An array of the roots in this grammar
    struct G_node *first;
    struct G_node *follow; 
    int num;
    int max;
}Grammar;

typedef struct G_node{
    enum Token token;       //!< Name of token, if NULL of type Grammar
    int grammar;            //!< Index of grammar in table (if token == NULL)
    struct G_node *next;    //!< next G_node in linked list, NULL if end
}G_node;

typedef struct Table{
    Grammar **table;        //!< A 2D array of pointers to grammars
    Grammar *grammars;      //!< An array of the grammars
    int num_grammars;
    int max_grammars;
}Table;


void gen_gram1();

Table *table_new();

Grammar *grammar_new(int size);

//! For generating a grammar
/*!
 \param gram pointer to grammar that this new "or" will be
 \param len the number of tokens 
 \param tokens[] an array of tokens in order of grammar, if NULL then corisponding next grammar[] is added
 \param grammars[] an array of pointers to grammars, if token has a NULL val then the next grammar will be added
*/
void grammar_add(Grammar *gram, int len, enum Token tokens[], int grammars[]);

Table *table_new(int num_grams);

int gen_first(Table *table);

int gen_follow(Table *table);

int gen_table();