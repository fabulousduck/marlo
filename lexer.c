#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lexer.h"

#define TOKEN_DEF_COUNT 3

//something people wont use in their .md files
//which we can use to return if a token is not
//a token we should do something special with
#define IS_NON_MD_TOKEN  '\0'


char is_md_token(char);

void lex_file(char * file_name)
{
    FILE *fp = fopen(file_name, "r");
    int current_char, j, i = 0;
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
            current_token.cargo += current_char;
        }
        tokens[i] = current_token;

        //printf("token %d > %s", i, current_token.cargo);
        ++i;
    }

    return;
}

char is_md_token(char token)
{
    int i;
    char * md_tokens = "#=-";

    for(i = 0; i < TOKEN_DEF_COUNT; ++i) {
        if(token == md_tokens[i]) {
            return md_tokens[i];
        }
    }
    return IS_NON_MD_TOKEN;
}

Token peekn(FILE * fp, char type)
{
    int i = 1;
    Token token;
    char tok_acc[100];

    tok_acc[0] = type;

    while((char)fgetc(fp) == type) {
        tok_acc[i] = type;
        ++i;
    }
    token.size = sizeof(tok_acc) / sizeof(char);
    printf("%s\n", tok_acc);
    return token;
}


