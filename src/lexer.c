#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

#define TOKEN_DEF_COUNT 3

//something people wont use in their .md files
//which we can use to return if a token is not
//a token we should do something special with
#define IS_NON_MD_TOKEN  '\0'


static char is_md_token(char);
static int remaining_file_pointer_length(FILE *);
static char * peek_type(FILE*, char, char *);
static Token * new_token();
static Lexer * new_lexer();


Lexer * lex_file(char * file_name)
{
    FILE *fp = fopen(file_name, "r");
    int current_char;
    size_t char_count, token_count = 0;

    fseek(fp, 0, SEEK_END);
    char_count = ftell(fp);
    rewind(fp);

    Lexer *lexer = new_lexer(char_count);

    while((current_char = fgetc(fp)) != EOF) {

        char c;
        char * char_accum = malloc(remaining_file_pointer_length(fp));
        Token *current_token = malloc(sizeof(Token));

        if((c = is_md_token((char)current_char)) != IS_NON_MD_TOKEN) {
            Token * token = new_token(strlen(char_accum));

            peek_type(fp, c, char_accum);
            token->size = strlen(char_accum);
            token->cargo = malloc(current_token->size+1);
            strncpy(token->cargo, char_accum, token->size);

            lexer->tokens[token_count] = token;

            token_count += 1;

        } else {


        }

    }

    lexer->token_count = token_count;
    return lexer;
}

static Token * new_token()
{
    Token * token = malloc(sizeof(Token));
    token->size = sizeof(int);
    token->cargo = NULL;
}

static Lexer * new_lexer(size_t token_count)
{
    Lexer *lexer = malloc(sizeof(Lexer) +  token_count);
    lexer->token_count = 0;
    return lexer;
}

static char is_md_token(char token)
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

static int remaining_file_pointer_length(FILE * fp)
{
    long int current_file_pointer_position = ftell(fp);
    fseek(fp, current_file_pointer_position, SEEK_END);
    long int file_pointer_end_position = ftell(fp);
    fseek(fp, current_file_pointer_position, SEEK_SET);
    return file_pointer_end_position - current_file_pointer_position;

}

static char * peek_type(FILE * fp, char type, char * token_accumilator)
{
    int i = 1;
    token_accumilator[0] = type;

    while((char)fgetc(fp) == type) {
        token_accumilator[i] = type;
        ++i;
    }

    return token_accumilator;
}


