#include <stdio.h>
#include <stdbool.h>
#include "lexer.h"

#define TOKEN_DEF_COUNT 4

//something people wont use in their .md files
//which we can use to return if a token is not
//a token we should do something special with
#define IS_NON_MD_TOKEN  '\0'


char is_md_token(char);

void lex_file(char * file_name)
{
    FILE *fp = fopen(file_name, "r");
    int current_char, i = 0;
    size_t char_count;

    fseek(fp, 0, SEEK_END);
    char_count = ftell(fp);
    rewind(fp);

    Token tokens[char_count];

    while((current_char = fgetc(fp)) != EOF) {

        char c;
        Token current_token;

        if((c = is_md_token(current_char)) != IS_NON_MD_TOKEN) {
            current_token = peekn(fp, c);
        } else {
            current_token.size  = 1;
            current_token.cargo = current_char;
        }

        ++i;
    }

    return;
}

char is_md_token(char token)
{
    int i;
    char * md_tokens = "#=-";

    for(i = 0; i < TOKEN_DEF_COUNT-1; ++i) {
        if(token == md_tokens[i]) {
            return md_tokens[i];
        }
    }
    return IS_NON_MD_TOKEN;
}

Token peekn(FILE * fp, char type)
{
    int i = 0;
    char curr_tok;
    char * token_acc;
    Token token;

    while((curr_tok = (char)fgetc(fp)) == type) {
        token_acc[i] = curr_tok;
    }
    token.cargo = token_acc;
    token.size = sizeof(token_acc) / sizeof(char*);
    return token;
}


