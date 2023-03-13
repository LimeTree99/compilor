/*! \mainpage Compilor Documentation

 \section intro_sec Introduction

 This is the introduction.

 \section a Things to do

 1. Complete dfa.next_key()\n
    -currently basic functionality works\n
    -still have to go through and fix memory leeks (they're there)\n
    -still need panic mode\n
 2. get the symbol and put in table.\n 
    -do this in lexer() func\n 
    -read each symbol to file\n 
    -put in some kind of storage, linked list adding a next pointer to symbol struct?? (do this later)\n
 3. impliment some command line options as described in "Use" section\n
    
 4. impliment panic mode\n
    -look up what panic mode is\n
 5. if I feel like it\n
    -let underscores be in variables (change in token table)\n

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
    S           := <exp>;
    <exp>       := <dec> | <set> | <func-dec> | <func> 
    <exp>       := <branch> | <loop> | <return> | <print>

    <type>      := int | double | <var>
    <item>      := <bool> | <int> | <var> | <func>
    <op>        := + | - | * | / | % | < | > | >= | <= | <> | == | and | or

    <equ>       := A <equ'>
    <equ'>      := <op> A <equ'> | eps
    A           := <item> | not <equ> | ( <equ> )

    <dec>       := <type> <var> = <item>
    <dec>       := <type> <var> <dec'>
    <dec'>      := , <var> <dec'> | eps    

    <set>       := <var> = <item>

    <func-dec>  := def <var> ( B ) S fed | def <type> <var> ( B ) S fed
    B           := <type> B' | eps
    B'          := , <type> B' | eps

    <func>      := <var> ( C )
    C           := <equ> C' | eps
    C'          := , <equ> C' |eps

    <branch>    := if ( <equ> ) then S D fi
    D           := else if ( <equ> ) then S D | else S | eps

    <loop>      := while ( <equ> ) do S od

    <return>    := return <equ>

    <print>     := print ( <equ> )    

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

void lexer(FILE *code_fh){
    char buff[2][BUFF_SIZE];
    struct Dfa *dfa = generate_lex1();

    Symbol sym;
    
    int num_read;
    int hold = 0;
    int *buff_select = &hold;
    bool end = false;

    char sym_out[60];
    
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
            sym = next_key(dfa, &(buff[0][0]), curr, line_num, char_num);
            sym.line_num = line_num;
            sym.char_num = char_num_start;

            if (*(sym.lexeme) != '\0'){
                sprintf(sym_out, "<%s>", sym.lexeme);
                fprintf(SYMBOL_FH, "line: %-4d char: %-3d lex: %-12s token: <%s>\n", 
                        sym.line_num, 
                        sym.char_num, 
                        sym_out, 
                        sym.token);
            }

            //the contense of sym are a memory leak FIX IT!
            //although i might store sym in a linked list, so might be fine   
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

}


int main(int argc, char * argv[]){
    printf("start compilation\n");
    FILE *code_fh;

    check_file_name(argv[argc-1]);

    code_fh = fopen(argv[argc-1], "r");
    SYMBOL_FH = fopen("io/symbols.txt", "w");
    //ERROR_FH = fopen("io/error.txt", "w");

    if (!code_fh) error("failed to open file <%s>", argv[argc-1]);
    if (!SYMBOL_FH) SYMBOL_FH = stdout;
    if (!ERROR_FH) ERROR_FH = stdout;

    lexer(code_fh);

    fclose(code_fh);
    if (SYMBOL_FH != stdout) fclose(SYMBOL_FH);
    if (ERROR_FH != stdout) fclose(ERROR_FH);

    
    printf("end\n");
    return 0;
}