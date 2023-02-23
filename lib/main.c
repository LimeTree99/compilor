/*! \mainpage Compilor Documentation

 \section intro_sec Introduction

 This is the introduction.

 \section a Things to do

 1. Complete dfa.next_key()
    -currently basic functionality works
    -still have to go through and fix memory leeks (I'm sure they're there)
    -still need panic mode
 2. get the symbol and put in table.
    -do this in lexer() func
    -read each symbol to file
    -put in some kind of storage, linked list?? (do this later)
 3. impliment panic mode
    -look up what panic mode is
 4. if I feel like it
    -let underscores be in variables (change in token table)


 \section Use
 \
    SYNTAX
        comp [file]

        file: source code text file ending in .cp


*/

/*! \file main.c
 \brief main() and comand line input handeling.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "build.h"


#define COLOR_RESET  "\x1b[0m"
#define COLOR_RED    "\x1b[31m"
#define COLOR_GREEN  "\x1b[32m"


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
    struct Dfa *dfa = generate_lex1();

    Symbol sym;
    
    int num_read;
    int hold = 0;
    int *buff_select = &hold;
    int char_num = 0;
    bool end = false;
    
    int line_num = 1;

    char *curr_p = &(buff[0][0]);
    char **curr = &curr_p;            //a double pointer so that it can be changed in a function
            
    
    //read in the initial chars to the buff 
    num_read = fread(buff[0], sizeof(char), BUFF_SIZE-1, fh);
    buff[0][num_read] = '\0';
    num_read = fread(buff[1], sizeof(char), BUFF_SIZE-1, fh);
    buff[1][num_read] = '\0';


    while (!end){
        
        if (**curr == '\n'){
            line_num++;
            *curr += 1;
        }else if (**curr == '\0' && ((int)*curr - (int)&(buff[0][0]) + 1) % BUFF_SIZE != 0){
            end = true;
        }else if (**curr == ' ' || **curr == '\t'){
            *curr += 1;
        }else{
            
            sym = next_key(dfa, &(buff[0][0]), curr);
            
            printf("lex: <%s> token: <%s>\n", sym.lexeme, sym.token);
            

            if (*buff_select == 0 && (int)*curr - (int)&(buff[0][0]) >= BUFF_SIZE ||
                *buff_select == 1 && (int)*curr - (int)&(buff[0][0]) < BUFF_SIZE){
                

                *buff_select = !(*buff_select);
                num_read = fread(buff[*buff_select], sizeof(char), BUFF_SIZE-1, fh);
                buff[*buff_select][num_read] = '\0';
            }
            
            
            
        }
        

        //printf("char: %c buff_select: %d cursor:%d line: %d\n", **curr, *buff_select, ((int)*curr - (int)&(buff[0][0]) + 1) % BUFF_SIZE, line_num);

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



    struct Dfa *dfa = generate_lex1();
    printf("dfa: %d\n", *(dfa->token_table + (20 * CHARSET_SIZE) + ' '));


    printf("\n--------------\n");
    printf("end\n");
    return 0;
}