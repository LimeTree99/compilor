/*! \mainpage Compilor Documentation

 \section intro_sec Introduction

 Compilor for the EZ language

 \section a Things to do
 <pre>
 1. Complete dfa.next_key()
    -go over and check mem leaks
 2. impliment grammar
    -create the LL(0) table: similar to the DFA for x axis of grid is the <token> and 
        y is the token on the top of the stack. each element of the grid is a grammar struct
    -grammar struct: a linked list of tokens.
    -create strcture to hold LL(0) table in code, and structure to hold the 
    -create func to traverse the LL(0) table and the stack that is used for that
 3. impliment some command line options as described in "Use" section

 4. remove left factoring in grammar

 4. questions to ask
    -are there ways to organize variables in c in a similar way to python
        similar to the Name.1var Name.var2 Name.var3 ect. system
    -should I expand my grammar to that there are no "or" for each phrase 
    -given the grammar:
        A -> T | G
        T -> a B
        G -> a Q
        B -> b
        Q -> q
        --------------------
        A -> ab | aq
        --------------------
        A -> aT
        T -> b 
        T -> q

    should I do this reduction for all of my grammar?
    I think this is a first/first conflict 
 </pre>

 \section . My problems with language specifications

 <pre>
    -there is no way to declare boolean values!!
 </pre>

 \section Use
 <pre>
    parameters marked as 'incomplete' may change or simply do not work
    SYNTAX
        comp [file] [param]

        file: source code text file ending in .cp

        param:
            '-o [file]' name & location of exicutable
            '-e [file]' specify name and location for error output
            '-s [file]' specify name and location for symbol table, 
                        if file is blank output wil go to stdout
 </pre>

 \section order File import order
 <pre>
    main
    ^
    grammar
    ^
    dfa
    ^
    string
    ^
    build
    ^
    general
 </pre>

 \section . Grammar
 <pre>
 notes: <word> denotes symbol, capital letter & {word} denotes grammar
    S           := {exp} <semi-col>
    {exp}       := {dec} | {set} | {func-dec} | {func} 
    {exp}       := {branch} | {loop} | {return} | {print}

    {type}      := <kw-int> | <kw-double> | <var>
    {item}      := <bool> | <int> | <var> | {func}
    {op}        := + | - | * | / | % | < | > | >= | <= | <> | == | and | or

    {arr-index} := [ <int> ] | eps

    {equ}       := A {equ'}
    {equ'}      := {op} A {equ'} | eps
    A           := {item} | not {equ} | ( {equ} )

    {dec}       := {type} <var> = {item}
    {dec}       := {type} <var> {arr-index} {dec'}
    {dec'}      := , <var> {dec'} | eps

    {set}       := <var> {arr-index} = {item}

    {func-dec}  := def <var> ( B ) S fed | def {type} <var> ( B ) S fed
    B           := {type} B' | eps
    B'          := , {type} B' | eps

    {func}      := <var> ( C )
    C           := {equ} C' | eps
    C'          := , {equ} C' |eps

    {branch}    := if ( {equ} ) then S D fi
    D           := else if ( {equ} ) then S D | else S | eps

    {loop}      := while ( {equ} ) do S od

    {return}    := return {equ}

    {print}     := print ( {equ} )    

 </pre>
*/

/*! \file main.c
 \brief main() and comand line input handeling.
*/
#include "grammar.h"


void check_file_name(char *name){
    int len = str_len(name);
    if (str_cmp(".cp", name+len-3) == false){
        error("invalaid document type");
        exit(1);
    }
}

Symbol *lexer(FILE *code_fh){
    char buff[2][BUFF_SIZE];
    struct Dfa *dfa = generate_lex1();

    Symbol sym;
    Symbol *root_sym = NULL;
    Symbol *cur_sym;
    
    int num_read;
    int hold = 0;
    int *buff_select = &hold;
    bool end = false;
    
    int line_num = 1;
    int hold2 = 0;
    int *char_num = &hold2;
    int char_num_start;

    char *curr_p = &(buff[0][0]);
    char **curr = &curr_p;            //a double pointer so that it can be changed in a function
            
    
    //read in the initial chars to the buff 
    num_read = fread(buff[0], sizeof(char), BUFF_SIZE-1, code_fh);
    buff[0][num_read] = '\0';
    num_read = fread(buff[1], sizeof(char), BUFF_SIZE-1, code_fh);
    buff[1][num_read] = '\0';

    while (!end){
        
        if (**curr == '\0'){
            if ( ((int)*curr - (int)&(buff[0][0]) + 1) == (BUFF_SIZE*2)){
                *curr = &(buff[0][0]);
            }else if ( ((int)*curr - (int)&(buff[0][0]) + 1) == BUFF_SIZE){
                *curr += 1;
            }else if ( ((int)*curr - (int)&(buff[0][0]) + 1) % BUFF_SIZE != 0 ){
                end = true;
            } 
        }else if (**curr == '\n'){
            line_num++;
            *char_num = 0;
            *curr += 1;
        }else if (**curr == ' ' || **curr == '\t'){
            *curr += 1;
            *char_num += 1;
        }else{
            char_num_start = *char_num;
            if (root_sym == NULL){
                
                root_sym = next_key(dfa, &(buff[0][0]), curr, line_num, char_num);
                while (root_sym->token == err){
                    free(root_sym);
                    root_sym = next_key(dfa, &(buff[0][0]), curr, line_num, char_num);
                }
                cur_sym = root_sym;
                
            }else{
                cur_sym->next = next_key(dfa, &(buff[0][0]), curr, line_num, char_num);
                if (cur_sym->next->token == err){
                    free(cur_sym->next);
                }else{
                    cur_sym = cur_sym->next;
                }
            }
            cur_sym->line_num = line_num;
            cur_sym->char_num = char_num_start;
            
            pr_symbol(SYMBOL_FH, cur_sym);
            
        }        
        //swap and read in buffer if curr has noved to the next buffer
        if (*buff_select == 0 && (int)*curr - (int)&(buff[0][0]) >= BUFF_SIZE ||
            *buff_select == 1 && (int)*curr - (int)&(buff[0][0]) < BUFF_SIZE){
            
            *buff_select = !(*buff_select);
            num_read = fread(buff[!(*buff_select)], sizeof(char), BUFF_SIZE-1, code_fh);
            buff[!(*buff_select)][num_read] = '\0';
            
        }
        //printf("char: %c buff_select: %d cursor:%d line: %d\n", **curr, *buff_select, ((int)*curr - (int)&(buff[0][0]) + 1) % BUFF_SIZE, line_num);
    }

    cur_sym->next = NULL;

    return root_sym;

}


void grammar(Symbol *root){
    Symbol *cur_sym = root;

    while (cur_sym != NULL){
        //pr_symbol(stdout, cur_sym);
        cur_sym = cur_sym->next;
    }
}


int main(int argc, char * argv[]){
    printf("start compilation\n");
    FILE *code_fh;
    Symbol *root;

    check_file_name(argv[argc-1]);

    code_fh = fopen(argv[argc-1], "r");
    SYMBOL_FH = fopen("io/symbols.txt", "w");
    ERROR_FH = fopen("io/error.txt", "w");

    if (!code_fh) error("failed to open file <%s>", argv[argc-1]);
    if (!SYMBOL_FH) SYMBOL_FH = stdout;
    if (!ERROR_FH) ERROR_FH = stdout;
    
    root = lexer(code_fh);

    gen_gram1();
    grammar(root);


    fclose(code_fh);
    if (SYMBOL_FH != stdout) fclose(SYMBOL_FH);
    if (ERROR_FH != stdout) fclose(ERROR_FH);

    
    printf("end\n");
    return 0;
}