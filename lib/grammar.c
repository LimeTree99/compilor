#include "grammar.h"


//private func
void table_addgram(Table *table, Grammar *gram);
void pr_table(Table *table);
void grammar_gen_fol(Table *table, int gram);
void grammar_gen_fir(Grammar *grammar);

void list_append_node(G_node **root, enum Token add);
void list_add_list(G_node **root, G_node *add_root);

//! Search list for token if found return index, if not return -1
int list_search(G_node *root, enum Token token);


void gen_gram2(){
    int len;
    //s =: <var> <eq> <semi-col>
    Table *table = table_new(10); 
    Grammar *s = grammar_new(10);
    Grammar *t = grammar_new(10);
    Grammar *b = grammar_new(10);


    enum Token s_tokens[][3] = {{var,err,err},
                                {var, err},
                                {eps}
                               };
    int s_grams[][2] = {{1,1},
                         {0},
                         {}
                         };

    len = 3;
    int sizes[] = {3,
                   2,
                   1
                  };
    for (int i=0; i < len; i++){
        grammar_add(s, sizes[i], s_tokens[i], s_grams[i]);
    }
    table_addgram(table, s);



    enum Token t_tokens[][5] = {{var,l_round, err, eq,semi_col},
                                {var, err, eq}
                               };
    int t_grams[][2] = {{0},
                             {0}
                            };
    
    len = 2;
    int t_sizes[] = {5,
                   3
                  };
    for (int i=0; i < len; i++){
        grammar_add(t, t_sizes[i], t_tokens[i], t_grams[i]);
    }

    table_addgram(table, t);

    enum Token b_tokens[][5] = {{eq,l_round, err, eq,semi_col},
                                {eq, err, err}
                               };
    int b_grams[][2] = {{0},
                        {0, 1}
                        };
    
    len = 2;
    int b_sizes[] = {5,
                   3
                  };
    for (int i=0; i < len; i++){
        grammar_add(b, b_sizes[i], b_tokens[i], b_grams[i]);
    }

    table_addgram(table, b);
    gen_first(table);
    gen_follow(table);
    pr_table(table);    
}

void gen_gram1(){
    
    const int num_grams = 19;
    Table *table = table_new(num_grams);
    Grammar *grammar[num_grams];
    for (int i=0; i < num_grams; i++){
        grammar[i] = grammar_new(13);
    }
    printf("a\n");
    enum Token tokens[][13][13] = 
    {
        // 0 S
        {
            {kw_int,var,err},
            {kw_double,var,err},
            {var, err},
            {kw_def, err},
            {kw_if, l_round, err, r_round, kw_then, err, err, kw_fi, semi_col},
            {kw_while, l_round, err, r_round, kw_do, err, kw_od, semi_col},
            {kw_return, err, semi_col},
            {kw_print, l_round, err, r_round, semi_col}
        },
        // 1 Z
        {
            {eq, err, semi_col},
            {l_square, err, r_square, err, semi_col},
            {err, semi_col}
        },
        // 2 X
        {
            {var, err},
            {kw_int, var, l_round, err, r_round, err, kw_fed, semi_col},
            {kw_double, var, l_round, err, r_round, err, kw_fed, semi_col}
        },
        // 3 U
        {
            {l_round, err, r_round, err, kw_fed, semi_col},
            {var, l_round, err, r_round, err, kw_fed, semi_col}
        },
        // 4 W
        {
            {l_round, err, r_round, semi_col},
            {l_square, err, r_square, eq, err, semi_col},
            {eq, err, semi_col},
            {var, err}
        },
        // 5 D
        {
            {kw_else, err},
            {eps}
        },
        // 6 E
        {
            {kw_if, l_round, err, r_round, kw_then, err, err},
            {err}
        },
        // 7 {equ}
        {
            {err, err}
        },
        // 8 {equ'}
        {
            {err, err, err},
            {eps}
        },
        // 9 A
        {
            {err},
            {kw_not, err},
            {l_round, err, r_round}
        },
        // 10 {type}
        {
            {kw_int},
            {kw_double},
            {var}
        },
        // 11 {item}
        {
            {kw_double},
            {kw_int},
            {var}
        },
        // 12 V
        {
            {l_round, err, r_round, semi_col},
            {eps}
        },
        // 13 {dec'}
        {
            {comma, var, err},
            {eps}
        },
        // 14 B
        {
            {err, err},
            {eps}
        },
        // 15 B'
        {
            {comma, err, err},
            {eps}
        },
        // 16 C
        {
            {err, err},
            {eps}
        },
        // 17 C'
        {
            {comma, err, err},
            {eps}
        },
        // 18 {op}
        {
            {add},
            {sub},
            {mult},
            {_div},
            {mod},
            {le},
            {gr},
            {gr_eq},
            {le_eq},
            {not_eq},
            {eq},
            {kw_and},
            {kw_or}
        }
    };
    
    int grams[][8][3] = 
    {
        // 0 S
        {
            {1},
            {1},
            {4},
            {2},
            {7,0,5},
            {7,0},
            {7},
            {7}
        },
        // 1 Z
        {
            {11},
            {11,13},
            {13}
        },
        // 2 X
        {
            {3},
            {14,0},
            {14,0}
        },
        // 3 U
        {
            {14,0},
            {14,0}
        },
        // 4 W
        {
            {16},
            {11,11},
            {11},
            {1}
        },
        // 5 D
        {
            {6}
        },
        // 6 E
        {
            {7,0,5},
            {0}
        },
        // 7 {equ} 
        {
            {9,8}
        },
        // 8 {equ'}
        {
            {18,9,8}
        },
        // 9 A
        {
            {11},
            {7},
            {7}
        },
        // 10 {type}
        {
            {}
        },
        // 11 {item}
        {
            {},
            {},
            {12}
        },
        // 12 V
        {
            {16}
        },
        // 13 {dec'}
        {
            {13}
        },
        // 14 B
        {
            {10,15}
        },
        // 15 B'
        {
            {10,15}
        },
        // 16 C
        {
            {7,17}
        },
        // 17 C'
        {
            {7,17}
        },
        // 18 {op}
        {
            {}
        }
    };
    int len[] = 
    {
        8, 3, 3, 2, 4, 2, 2, 1, 2, 3, 3, 3, 2, 2, 2, 2, 2, 2, 13
    };
    int sizes[][13] = 
    {
        // 0 S
        {3,3,2,2,9,8,3,5},
        // 1 Z
        {3,5,2},
        // 2 X
        {2,8,8},
        // 3 U
        {6,7},
        // 4 W
        {4,5,3,2},
        // 5 D
        {2,1},
        // 6 E
        {7,1},
        // 7 {equ}
        {2},
        // 8 {equ'}
        {3,1},
        // 9 A
        {1,2,3},
        // 10 {type}
        {1,1,1},
        // 11 {item}
        {1,1,2},
        // 12 V
        {4, 1},
        // 13 {dec'}
        {3,1},
        // 14 B
        {2,1},
        // 15 B'
        {3,1},
        // 16 C
        {2,1},
        // 17 C'
        {3,1},
        // 18 {op}
        {1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    for (int gram_i=0; gram_i < num_grams; gram_i++){
        
        for (int or_i=0; or_i < len[gram_i]; or_i++){
            printf("gram_i: %d or_i: %d\n", gram_i, or_i);
            grammar_add(grammar[gram_i], 
                        sizes[gram_i][or_i], 
                        tokens[gram_i][or_i], 
                        grams[gram_i][or_i]);
        }
        table_addgram(table, grammar[gram_i]);
        
    }
    
    


    gen_first(table);
    gen_follow(table);
    pr_table(table);    
}

Grammar *grammar_new(int size){
    Grammar *gram = (Grammar*)malloc(sizeof(Grammar));
    gram->num = 0;
    gram->max = size;
    gram->roots = (G_node**)malloc(sizeof(G_node**)*size);
    gram->first = NULL;
    gram->follow = NULL;
    return gram;
}

void grammar_add(Grammar *gram, int len, enum Token tokens[], int grammars[]){
    G_node *cur;
    int i=0;
    int gram_i=0;

    if(gram->max == gram->num){
        error("Too many grammars, cannot add new grammar to roots in: grammar_add()");
    }

    while (i < len){
        
        if (i == 0){
            cur = (G_node*)malloc(sizeof(G_node));
            *(gram->roots + gram->num) = cur;
        }else{
            cur->next = (G_node*)malloc(sizeof(G_node));
            cur = cur->next;
        }

        if (tokens[i] == err){
            //add grammar
            cur->grammar = grammars[gram_i];
            cur->token = err;
            gram_i++;
        }else{
            cur->token = tokens[i];
            cur->grammar = -1;
        }
        i++;
    }
    cur->next = NULL;
    gram->num++;
    
}

Table *table_new(int num_grams){
    Table *table = (Table*)malloc(sizeof(Table*));
    table->grammars = (Grammar*)malloc(sizeof(Grammar) * num_grams);
    table->max_grammars = num_grams;
    table->num_grammars = 0;

    return table;
}

void table_addgram(Table *table, Grammar *gram){
    if (table->max_grammars == table->num_grammars){
        error("Too many grammars, cannot add new grammar to table in: table_addgram()");
    }
    *(table->grammars + table->num_grammars) = *gram;
    table->num_grammars++;
}

void set_table_row(Table *table){

}


int gen_first(Table *table){
    for (int i=0; i < table->num_grammars; i++){
        grammar_gen_fir((table->grammars + i));
    }
    
}

void grammar_gen_fir(Grammar *grammar){
    G_node *cur;
    enum Token token;
    
    for (int i=0; i < grammar->num; i++){
        token = (*(grammar->roots + i))->token;
        list_append_node(&(grammar->first), token);
    }
    
}

int gen_follow(Table *table){
    //add the $ to the start grammar
    list_append_node(&(table->grammars->follow), dollar);
    grammar_gen_fol(table, 0);
    
    for (int i=1; i<table->num_grammars; i++){
        //check that the follow hasn't already been generated
        if ((table->grammars + i)->follow == NULL){ 
            grammar_gen_fol(table, i);
        }   
    }
    
}

void grammar_gen_fol(Table *table, int gram){
    Grammar *gram_p = (table->grammars + gram);
    G_node *cur;

    G_node *cur_add;
    
    //this traverses through the whole table
    for (int j=0; j<table->num_grammars; j++){
        gram_p = (table->grammars + j);
        for (int i=0; i < gram_p->num; i++){      //each 'or' in same grammar
            cur = *(gram_p->roots + i);
            while(cur != NULL){                    //each token in grammar
                if (cur->token == err){ //if it is a grammar                    
                    if (cur->grammar == gram){
                        //found the grammar
                        //the following value is the one to add
                        if (cur->next == NULL){
                            //have to add the follow of gram_p
                            if (gram_p->follow == NULL){
                                //generate if doesn't exist
                                grammar_gen_fol(table, j);
                            }
                            list_add_list(&((table->grammars+gram)->follow),
                                          gram_p->follow);
                        }else if (cur->next->token == err){
                            //have to add the first of grammar in cur->next->grammar

                            list_add_list(&((table->grammars+gram)->follow), 
                                          (table->grammars + cur->next->grammar)->first);
                            
                        }else{
                            //add next token
                            
                            list_append_node(&((table->grammars+gram)->follow),
                                             cur->next->token);                          
                        }
                        
                    }
                }
                cur = cur->next;
            }
        }
    }
    
}

void list_append_node(G_node **root, enum Token add){
    G_node *cur = *root;

    //only add if token not already there
    if (list_search(*root, add) == -1){
        if (*root == NULL){
            *root = (G_node*)malloc(sizeof(G_node));
            cur = *root;
        }else{
            //find the end
            while (cur->next != NULL){
                cur = cur->next;
            }
            cur->next = (G_node*)malloc(sizeof(G_node));
            cur = cur->next;
        }
        cur->token = add;
        cur->next = NULL;
    }
}

void list_add_list(G_node **root, G_node *add_root){
    G_node *cur = add_root;

    while (cur != NULL){
        list_append_node(root, cur->token);
        cur = cur->next;
    }
}

int list_search(G_node *root, enum Token token){
    G_node *cur = root;
    int i=0;
    while (cur != NULL && cur->token != token){
        cur = cur->next;
        i++;
    }
    if (cur == NULL){
        i = -1;
    }
    return i;
}

void pr_table(Table *table){
    Grammar *cur_gram;
    G_node *cur;
    
    for (int j=0; j < table->num_grammars; j++){
        cur_gram = (table->grammars + j);
        printf("grammar %d\n", j);
        for (int i=0; i < cur_gram->num; i++){
            cur = *(cur_gram->roots + i);
            printf("\t");
            while(cur != NULL){
                if (cur->token == err){
                    printf("{gram %d} ", cur->grammar);
                }else{
                    printf("<%s> ", token_names[cur->token]);
                }
                cur = cur->next;
            }
            printf("\n");
        }

        printf("\n\tfirst: ");
        cur = cur_gram->first;
        while(cur != NULL){
            printf("<%s> ", token_names[cur->token]);
            cur = cur->next;
        }
        printf("\n");

        printf("\tfollow: ");
        cur = cur_gram->follow;
        while(cur != NULL){
            printf("<%s> ", token_names[cur->token]);
            cur = cur->next;
        }
        printf("\n");
    }
}

int gen_follow_r(Table *table, Grammar *cur){

}

int gen_table(){
    
}