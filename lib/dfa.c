#include "dfa.h"

struct Dfa *dfa_new(int max_nodes){
    struct Dfa *new_dfa = (struct Dfa *)malloc(sizeof(struct Dfa));
    new_dfa->token_table = (int *)malloc(sizeof(int) * max_nodes * CHARSET_SIZE);
    for (int i=0; i < max_nodes * CHARSET_SIZE; i++){
        *(new_dfa->token_table + i) = -1;  //assign the base value of link to -1
    }
    new_dfa->node_lex = (char **)malloc(sizeof(char *) * max_nodes);
    new_dfa->num_nodes = 0;
    new_dfa->max_nodes = max_nodes;
    return new_dfa;
}

struct Dfa *generate_lex1(){
    int num_nodes = 27;
    char *l_char[] = {"/d","/w","<",">","=","+","-","*","/","%","(",")","[","]",",",";",".","e",
                      ">","=",
                      "=",
                      "=",
                      "/d",
                      "/d",
                      "/d","/w","_",
                      "/d",".",
                      "/d",
                      "/d","e","E",
                      "/d","+","-",
                      "/d",
                      "/d"};
    int l_num[] = {21,20,1,2,3,7,8,9,10,11,12,13,14,15,16,17,18,20,
                   19,5,
                   6,
                   4,
                   21,
                   21,
                   20,20,20,
                   21,22,
                   23,
                   23,24,24,
                   26,25,25,
                   26,
                   26};
    int len[] = {18,2,1,1,
                 0,0,0,1,
                 1,0,0,0,
                 0,0,0,0,
                 0,0,0,0,
                 3,2,1,3,
                 3,1,1};

    char *token[] = {"\0","le","gr","asn",
                     "eq","le_eq","gr_eq","add",
                     "sub","mult","div","mod",
                     "l_round","r_round","l_square","r_square",
                     "comma","semi_col","end","not_eq",
                     "var","int","\0","double",
                     "\0","\0","double"};

    struct Dfa *dfa = dfa_new(num_nodes);
    int l_pos = 0;
    for (int i=0; i < num_nodes; i++){
        set_node(dfa, i, token[i], (l_char+l_pos), (l_num+l_pos), len[i]);
        l_pos += len[i];
    }
    return dfa;   
}

bool dfa_free(struct Dfa *dfa){
    free(dfa->token_table);
    free(dfa->node_lex);
    free(dfa);
    return true;
}

//work out how to deal with '\0' at both EOF and end of buff
//solution: if '\0' is encountered then
//1. if end of buff 1: curr++ (just keep going)
//2. if end of buff 2: curr = buff 
//3. else: you are at EOF return token.
// if token 
struct Symbol next_key(struct Dfa *dfa, char *buff, char *start){
    char *curr = start;
    int prev_node = 0;
    int node = 0;
    struct Symbol re_symbol;

    do{
        prev_node = node;
        node = *(dfa->token_table + (node * CHARSET_SIZE) + *curr);
        curr++;
    }while(node != 0 && *curr != '\0');

    if (node == 0){
        //symbol found
        //re_symbol.lexeme = 
    }

}

//creates dfa node, for use in testing
void set_node(struct Dfa *dfa, 
              int node, 
              char *lexeme, 
              char *link_char[], 
              int link_num[],
              int links_v){
    int *row = dfa->token_table + (node * CHARSET_SIZE);

    *(dfa->node_lex + node) = str_copy(lexeme);
    
    for (int i=0; i<links_v; i++){

        if (link_char[i][0] == '/'){
            //special multichar nodesetting
            if(link_char[i][1] == '/'){
                //just '/'
                *(row + '/') = link_num[i];
            }else if (link_char[i][1] == 'w'){
                //[a-zA-z]
                
                for (int j='A'; j <= 'Z'; j++){
                    //capitals
                    *(row + j) = link_num[i];
                }
                for (int j='a'; j <= 'z'; j++){
                    //lowercase
                    *(row + j) = link_num[i];
                }

            }else if (link_char[i][1] == 'd'){
                //[0-9]
                for (int j='0'; j <= '9'; j++){
                    *(row + j) = link_num[i];
                }
            }
        }else{
            *(row + link_char[i][0]) = link_num[i];
        }

        
    }
}