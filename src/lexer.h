typedef struct token_t {
    int size;
    char * cargo;
} Token;

typedef struct lexer_t {
    size_t token_count;
    Token *tokens[];
} Lexer;

Lexer * lex_file(char*);

