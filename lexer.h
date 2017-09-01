typedef struct token_t {
    int size;
    char * cargo;
} Token;

typedef struct lexer_t {
    int token_count;
    Token tokens[];
} Lexer;

Lexer * lex_file(char*);

