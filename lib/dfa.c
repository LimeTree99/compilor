#include "dfa.h"

struct Dfa *generate_lex1(){
    int num_nodes = 27;
    char *l_char[] = {"/d","/w","<",">","=","+","-","*","/","%","(",")","[","]",",",";",".","e",
                      ">","=",
                      "=",
                      "=",
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
                   20,20,20,
                   21,22,
                   23,
                   23,24,24,
                   26,25,25,
                   26,
                   26};
    int len[] = {18,2,1,1,
                 0,0,0,0,
                 0,0,0,0,
                 0,0,0,0,
                 0,0,0,0,
                 3,2,1,3,
                 3,1,1};

    char *token[] = {"\0","le","gr","asn",
                     "eq","le_eq","gr_eq","add",
                     "sub","mult","div","mod",
                     "l_round","r_round","l_square","r_square",
                     "comma","semi_col","end","not_eq",
                     "var","int","double","double",
                     "\0","\0","double"};

    struct Dfa *dfa = dfa_new(num_nodes);
    int l_pos = 0;
    for (int i=0; i < num_nodes; i++){
        set_node(dfa, i, token[i], (l_char+l_pos), (l_num+l_pos), len[i]);
        l_pos += len[i];
    }
    return dfa;   
}

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

bool dfa_free(struct Dfa *dfa){
    free(dfa->token_table);
    free(dfa->node_lex);
    free(dfa);
    return true;
}

 
Symbol next_key(struct Dfa *dfa, 
                char *buff, 
                char **cursor, 
                int *char_num, 
                FILE *error_fh){
    int prev_node = 0;
    int node = 0;
    bool end = false;
    int token_i = 0;
    char token[BUFF_SIZE];
    Symbol re_symbol;

    int i;

    char *start = *cursor;
    int start_char_num = *char_num;

    while (!end){
        if (**cursor == '\0'){
            if ( ((int)*cursor - (int)buff + 1) % BUFF_SIZE != 0 ){
                end = true;
            }else if (((int)*cursor - (int)buff + 1) >= BUFF_SIZE * 2){
                *cursor = buff;
            }else{
                *cursor += 1;
            }
        }
             
        prev_node = node;
        node = *(dfa->token_table + (node * CHARSET_SIZE) + **cursor);

        token[token_i] = **cursor;

        if (node == 0){
            end = true;
        }else if (node == -1){
            end = true;
        }else{ 
            *char_num += 1; 
            token_i++;
            *cursor += 1;
        }

    }
    token[token_i] = '\0';

    re_symbol.token = str_copy(token);

    re_symbol.lexeme = str_copy(*(dfa->node_lex + prev_node));

    if ( str_cmp(re_symbol.lexeme, "var") ){
        //check if variable is of type "keyword"
        i=0;
        end=false;
        while (!end && i < NUM_KEYWORDS){
            if (str_cmp(token, keywords[i])){
                re_symbol.lexeme = "keyword";
            }
            i++;
        }
    }else if ( *(re_symbol.lexeme) == '\0'){
        //log error and retry
        fprintf(error_fh, "Lexical Error: unknown symbol <%s>\n", re_symbol.token);

        *(*cursor-1) = ' '; //try changing the errored char to a space

        *cursor = start;
        *char_num = start_char_num;
        re_symbol = next_key(dfa, buff, cursor, char_num, error_fh);

    }
    
    return re_symbol;

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