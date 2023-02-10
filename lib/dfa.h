

#define CHARSET_SIZE 255

struct Dfa{
    int *grid;
    char **node_lex;  //if '\0' then not a final node (panic mode)
    int num_nodes;
    int max_nodes;
}Dfa;

struct Symbol{
    char *token;
    char *lexeme;
}Symbol;