/*
Author: Erin Hemsley
ID:     180109120
--------------------
main() function held here
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "string.h"
#include "build.h"


#define COLOR_RESET  "\x1b[0m"
#define COLOR_RED    "\x1b[31m"
#define COLOR_GREEN  "\x1b[32m"

#define BUFF_SIZE 100
#define CHARSET_SIZE 255


struct Symbol{
    char *token;
    char *lexeme;
}Symbol;

struct Dfa{
    int *grid;
    char **node_lex;  //if '\0' then not a final node (panic mode)
    int num_nodes;
    int max_nodes;
}Dfa;


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

void error(char *message, ...){
    va_list args;
    va_start(args, message);
    printf(COLOR_RED);
    printf("Compiler Error: "); 
    printf(COLOR_RESET);
    vprintf(message, args);
    printf("\n");
    exit(1);
}

void check_file_name(char *name){
    int len = str_len(name);
    if (str_cmp(".cp", name+len-3) == false){
        error("invalaid document type");
        exit(1);
    }

}

void lexer(FILE *fh){
    char buff[2][BUFF_SIZE];
    int select_buff = 0;
    int cursor = 0;
    int n = 0;
    char curr;
    bool end = false;

    int num_read;
    
    

    fread(buff[0], sizeof(char), BUFF_SIZE-1, fh);
    buff[0][BUFF_SIZE-1] = '\0';
    curr = buff[0][0];

    while (!end){
        if (curr == '\0'){
            if ((n+1) % BUFF_SIZE == 0){
                cursor = -1;
                if (select_buff == 0) {
                    select_buff = 1;
                }else{
                    select_buff = 0;
                }
                num_read = fread(buff[select_buff], sizeof(char), BUFF_SIZE-1, fh);
                
                buff[select_buff][num_read] = '\0';
                
                
            }else{
                end = true;
            }
        }else{
            //here goes the acctual lexer code 
            printf("%c", curr);
        }
        cursor++;
        n++;
        curr = buff[select_buff][cursor];
    }
    
}


int main(int argc, char * argv[]){
    printf("start\n");
    printf("The lexer:\n");
    printf("---------------\n");
    FILE *fh;

    check_file_name(argv[argc-1]);

    fh = fopen(argv[argc-1], "r");
    if (fh){
        lexer(fh);

        fclose(fh);
    }else{
        error("failed to open file <%s>", argv[argc-1]);
    }
    printf("\n--------------\n");
    printf("DNF testing:\n");
    printf("--------------\n");
    struct Dfa *eq = dfa_new(10);
    int arr[] = {'>',1,'=',3};
    set_node(eq, 0, "le", arr, 4);

    printf("key1: %s\n", keywords[1]);

    printf("\n--------------\n");
    printf("end\n");
    return 0;
}