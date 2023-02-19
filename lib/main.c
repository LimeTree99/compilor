/*! \mainpage Compilor Documentation

 \section intro_sec Introduction

 This is the introduction.

 \section a Things to do

 1. fix up the main.lexer() so it doesn't bother with '\0' (this is now the job of new_key())
 1.5 figure out how to addvance the buff 
 2. Complete dfa.next_key()

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

#define BUFF_SIZE 100   //!currently no safeguard if token is longer than BUFF_SIZE



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

//this function needs to go through the file and remove 
//concurrent spaces, /n, and /t chars
//do in a stream

//unicode is not allowed! only ascii!
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
            //here is a stream of all chars except '\0'
            //need to impliment a way of holing off on pulling new buff
            //when there is a token split between two buffers

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



    struct Dfa *dfa = generate_lex1();
    printf("dfa: %d\n", *(dfa->token_table + (20 * CHARSET_SIZE) + 'a'));


    printf("\n--------------\n");
    printf("end\n");
    return 0;
}