typedef struct token_t {
    int size;
    char * cargo;
} Token;

void lex_file(char*);
bool is_md_token(char*);
Token * peekn(FILE*, char);
