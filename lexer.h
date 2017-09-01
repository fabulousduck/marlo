typedef struct token_t {
    int size;
    char * cargo;
} Token;

void lex_file(char*);
char is_md_token(char);
char * peek_type(FILE*, char, char *);
