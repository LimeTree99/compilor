#include "grammar.h"


//private func
void table_addgram(Table *table, Grammar *gram);
void pr_table(Table *table);
void grammar_gen_fol(Table *table, Grammar *grammar);
void list_add_token(G_node **root, G_node **cur, enum Token add);


void gen_gram1(){
    //s =: <var> <eq> <semi-col>
    Table *table = table_new(10); 
    Grammar *s = grammar_new(10);
    Grammar *t = grammar_new(10);


    enum Token s_tokens[][3] = {{var,eq,semi_col},
                                {var, err}
                               };
    Grammar *s_grams[][2] = {{},
                             {s}
                            };
    
    grammar_add(s, 3, s_tokens[0], s_grams[0]);
    grammar_add(s, 2, s_tokens[1], s_grams[1]);

    table_addgram(table, s);

    enum Token t_tokens[][5] = {{var,l_round, err, r_round,semi_col},
                                {var, err, semi_col}
                               };
    Grammar *t_grams[][2] = {{s},
                             {s}
                            };
    
    grammar_add(t, 5, t_tokens[0], t_grams[0]);
    grammar_add(t, 3, t_tokens[1], t_grams[1]);

    table_addgram(table, t);

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

void grammar_add(Grammar *gram, int len, enum Token tokens[], Grammar *grammars[]){
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
            cur->grammar = NULL;
        }
        i++;
    }
    cur->next = NULL;
    gram->num++;
}

Table *table_new(int num_grams){
    Table *table = (Table*)malloc(sizeof(Table*));
    table->grammars = (Grammar**)malloc(sizeof(Grammar*) * num_grams);
    table->max_grammars = num_grams;
    table->num_grammars = 0;

    return table;
}

void table_addgram(Table *table, Grammar *gram){
    if (table->max_grammars == table->num_grammars){
        error("Too many grammars, cannot add new grammar to table in: table_addgram()");
    }
    *(table->grammars + table->num_grammars) = gram;
    table->num_grammars++;
}

void set_table_row(Table *table){

}


int gen_first(Table *table){
    
}

int gen_follow(Table *table){
    grammar_gen_fol(table, *(table->grammars + 0));
}

void grammar_gen_fol(Table *table, Grammar *grammar){
    Grammar *f_gram = grammar;        //the grammar currently being looked through for all follows 
    Grammar *cur_gram;
    G_node *cur;

    G_node *cur_add;
    

    //this traverses through the whole table
    for (int j=0; j < table->num_grammars; j++){
        cur_gram = *(table->grammars + j);
        for (int i=0; i < cur_gram->num; i++){
            cur = *(cur_gram->roots + i);
            while(cur != NULL){
                if (cur->token == err){
                    
                    if (cur->grammar == f_gram){
                        //found the grammar
                        //the following value is the one to add
                        if (cur->next == NULL){
                            //have to add the follow of cur_gram
                        }else if (cur->next->token == err){
                            //have to add the first of grammar in cur->next->grammar
                            if (cur->next->grammar == cur_gram){
                                //this is a recursive grammar 
                                //do not make an infinite loop
                            }else{
                                //non recursive grammar
                            }
                        }else{
                            //add next as a follow

                            list_add_token(&(f_gram->follow), &cur_add, cur->next->token);                          
                        }
                        
                    }
                }

                cur = cur->next;
            }
        }
    }
}

void list_add_token(G_node **root, G_node **cur, enum Token add){
    if (*root == NULL){
        *root = (G_node*)malloc(sizeof(G_node));
        *(cur) = *root;
        printf("a\n");
    }else{
        (*cur)->next = (G_node*)malloc(sizeof(G_node));
        *cur = (*cur)->next;
    }
    (*cur)->token = add;
    (*cur)->next = NULL;
}

void pr_table(Table *table){
    Grammar *cur_gram;
    G_node *cur;
    
    for (int j=0; j < table->num_grammars; j++){
        printf("grammar %d\n", j);
        cur_gram = *(table->grammars + j);
        for (int i=0; i < cur_gram->num; i++){
            cur = *(cur_gram->roots + i);
            printf("\t");
            while(cur != NULL){
                printf("<%s> ", token_names[cur->token]);
                cur = cur->next;
            }
            printf("\n");
        }

        printf("\n\tfirst: ");
        cur = cur_gram->first;
        while(cur != NULL){
            printf("<%s>, ", token_names[cur->token]);
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