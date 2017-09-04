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
static char * peek_untill_symbol(FILE*, char, char *);
static Lexer * new_lexer();


Lexer * lex_file(char * file_name)
{
    FILE *fp = fopen(file_name, "r");
    int current_char, j, i = 0;
    size_t char_count;
    Lexer *lexer = new_lexer();

    fseek(fp, 0, SEEK_END);
    char_count = ftell(fp);
    rewind(fp);

    Token tokens[char_count];

    while((current_char = fgetc(fp)) != EOF) {

        char c;
        Token current_token;

        if((c = is_md_token(current_char)) != IS_NON_MD_TOKEN) {
            char char_accum [remaining_file_pointer_length(fp)];
            char * full_token_cargo = peek_type(fp, c, char_accum);
            current_token.size = strlen(full_token_cargo);
            current_token.cargo = malloc(strlen(full_token_cargo)+1);
            strcpy(current_token.cargo, full_token_cargo);
        } else {
            char char_accum[remaining_file_pointer_length(fp)];
            char * full_token_cargo = peek_untill_symbol(fp, c, char_accum);
            current_token.size = strlen(full_token_cargo);
            current_token.cargo = malloc(strlen(full_token_cargo)+1);
            strcpy(current_token.cargo, full_token_cargo);
        }
        lexer->tokens[i] = current_token;
    }

    return lexer;
}

static Lexer * new_lexer()
{
    Lexer *lexer = malloc(sizeof(Lexer));
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

static char * peek_untill_symbol(FILE *fp, char base ,char * token_accumilator)
{
    int i = 1;
    token_accumilator[0] = base;
    char c;
    while((is_md_token(c = (char)fgetc(fp))) != IS_NON_MD_TOKEN) {
        token_accumilator[i] = c;
        ++i;
    }

    return token_accumilator;
}
