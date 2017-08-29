#include <stdio.h>
#include <stdbool.h>
#include "lexer.h"

#define TOKEN_COUNT 3

bool is_md_token(char);

char * md_tokens[TOKEN_COUNT] = {
    "#", "=", "-"
};

void lex_file(char * file_name)
{
    FILE *fp = fopen(file_name, "r");
    int i = 0;
    int curr_token_char;
    size_t char_count;
    fseek(fp, 0, SEEK_END);
    char_count = ftell(fp);
    rewind(fp);

    while((curr_token_char = fgetc(fp)) != EOF) {
        Token * curr_token;
        if(is_md_token((char)curr_token_char)) {
            switch((char)curr_token_char) {
                case '#':
                    curr_token = peekn(fp, '#');
                case '=':
                    curr_token = peekn(fp, '=');
                case '-':
                    curr_token = peekn(fp, '-');
                default:
                    curr_token->size = 1;
                    curr_token->cargo = (char*)curr_token_char;
            }
        }
        printf("token size: %d\n token content %s;", curr_token->size, curr_token->cargo);
        ++i;
    }
    printf("done");
    return;
}

bool is_md_token(char token)
{
    int i;
    for(i = 0; i < TOKEN_COUNT-1; ++i) {
        if(token == md_tokens[i]) {
            return true;
        }
    }
    return false;
}

Token * peekn(FILE * fp, char type)
{
    int i = 0;
    char curr_tok;
    char * token_acc;
    Token * token;

    while((curr_tok = (char)fgetc(fp)) == type) {
        token_acc[i] = curr_tok;
    }
    token->cargo = token_acc;
    token->size = sizeof(token_acc) / sizeof(char*);
    return token;
}


