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


 \section Use
 <pre>
    parameters marked as 'incomplete' may change or simply do not work
    SYNTAX
        comp [file] [param]

        file: source code text file ending in .cp

        param:
            '-stext'    output the symbol table as readable text    (incomplete)
            '-sbin'     output symbol table as binary               (incomplete)
 </pre>

 \section order File import order
 <pre>
    main
    ^
    dfa
    ^
    string
    ^
    build
    ^
    general
 </pre>
*/

/*! \file main.c
 \brief main() and comand line input handeling.
*/
#include "dfa.h"


void check_file_name(char *name){
    int len = str_len(name);
    if (str_cmp(".cp", name+len-3) == false){
        error("invalaid document type");
        exit(1);
    }
}

void lexer(FILE *code_fh, FILE *symbol_fh, FILE *error_fh){
    char buff[2][BUFF_SIZE];
    struct Dfa *dfa = generate_lex1();

    Symbol sym;
    
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
            sym = next_key(dfa, &(buff[0][0]), curr, char_num, error_fh);
            sym.line_num = line_num;
            sym.char_num = char_num_start;
            
            fprintf(symbol_fh, "line: %d, char: %d, lex: <%s>, token: <%s>\n", 
                    sym.line_num, 
                    sym.char_num, 
                    sym.lexeme, 
                    sym.token);

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
    FILE *symbol_fh;
    FILE *error_fh;

    check_file_name(argv[argc-1]);

    code_fh = fopen(argv[argc-1], "r");
    symbol_fh = fopen("io/symbols.txt", "w");
    error_fh = fopen("io/error.txt", "w");

    if (!code_fh) error("failed to open file <%s>", argv[argc-1]);
    if (!symbol_fh) symbol_fh = stdout;
    if (!error_fh) error_fh = stdout;

    lexer(code_fh, symbol_fh, error_fh);

    fclose(code_fh);
    fclose(symbol_fh);

    
    printf("end\n");
    return 0;
}