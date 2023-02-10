#include "dfa.h"

struct Dfa *dfa_new(int max_nodes){
    struct Dfa *new_dfa = (struct Dfa *)malloc(sizeof(struct Dfa));
    new_dfa->grid = (int *)malloc(sizeof(int) * max_nodes * CHARSET_SIZE);
    for (int i=0; i < max_nodes * CHARSET_SIZE; i++){
        *(new_dfa->grid + i) = -1;  //assign the base value of link to -1
    }
    new_dfa->node_lex = (char **)malloc(sizeof(char *) * CHARSET_SIZE);
    new_dfa->num_nodes = 0;
    new_dfa->max_nodes = max_nodes;
    return new_dfa;
}

/*
work out how to deal with '\0' at both EOF and end of buff
-----------------------------------
struct Dfa *dfa:
    dfa used to analize characters
char *start:
    first char and will incriment from there until symbol is found
returns:
    struct Symbol: containing the next sybol starting with <start>
*/
struct Symbol next_key(struct Dfa *dfa, char *start){
    char *curr = start;
    int prev_node = 0;
    int node = 0;
    struct Symbol re_symbol;

    do{
        prev_node = node;
        node = *(dfa->grid + (node * CHARSET_SIZE) + *curr);
        curr++;
    }while(node != 0 && *curr != '\0');

    if (node == 0){
        //symbol found
        //re_symbol.lexeme = 
    }

}

//creates dfa node, for use in testing
void set_node(struct Dfa *dfa, int node, char *final, int links[], int links_v){
    int final_len = str_len(final);
    printf("final: %d\n", final_len);
    int *row = dfa->grid + (node * CHARSET_SIZE);

    
    *(dfa->node_lex + node) = str_copy(final);
    

    for (int i=0; i<links_v; i=i+2){
        *(row + links[i]) = links[i+1];
    }
}