#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

//something people wont use in their .md files
//which we can use to return if a token is not
//a token we should do something special with
#define IS_NON_MD_TOKEN  '\0'


static char is_md_token(char);
static int remaining_file_pointer_length(FILE *);
static char * peek_type(FILE*, char, char *);
static char * peek_chars(FILE *, char, char *);
static char * determine_token_type(char);
static Token * new_token();
static Lexer * new_lexer();


Lexer * lex_file(char * file_name)
{
    FILE *fp = fopen(file_name, "rb");
    int current_char;
    size_t char_count, token_count = 0;

    fseek(fp, 0, SEEK_END);
    char_count = ftell(fp);
    rewind(fp);

    Lexer *lexer = new_lexer(char_count);

    while((current_char = fgetc(fp)) != EOF) {

        char c;
        char * char_accum = malloc(remaining_file_pointer_length(fp));
        char * token_type;
        Token * token = new_token();

        if((c = is_md_token((char)current_char)) != IS_NON_MD_TOKEN) {
            peek_type(fp, c, char_accum);
            token_type = determine_token_type(char_accum[0]);
        } else {
            peek_chars(fp, current_char, char_accum);
            token_type = "char_string";
        }

        token->size = strlen(char_accum) +1;
        token->cargo = malloc(token->size);
        token->type = malloc(strlen(token_type) +1);
        memcpy(token->type, token_type, strlen(token_type) +1);
        memcpy(token->cargo, char_accum, token->size);
        lexer->tokens[token_count] = token;

        token_count += 1;
    }

    lexer->token_count = token_count;
    return lexer;
}

static Token * new_token()
{
    Token * token = malloc(sizeof(Token));
    token->size = sizeof(int);
    token->cargo = NULL;
    token->type = NULL;
    return token;
}

static Lexer * new_lexer(size_t token_count)
{
    Lexer *lexer = malloc(sizeof(Lexer) +  token_count);
    lexer->token_count = 0;
    return lexer;
}


static char * determine_token_type(char sample)
{
    char * type;
    switch(sample) {
        case '#':
            type = "heading";
            break;
        case '-':
        case '=':
            type = "blank_line";
            break;
        case '*':
            type = "star";
            break;
        case '`':
            type = "tilde";
            break;
    }
    return type;
}

static char is_md_token(char token)
{
    int i;
    md_token md_tokens[5] = {
        {'='},
        {'*'},
        {'-'},
        {'#'},
    };

    for(i = 0; i < (sizeof(md_tokens)/sizeof(md_token)); ++i) {
        if(token == md_tokens[i].md_token_char) {
            return md_tokens[i].md_token_char;
        }
    }
    return IS_NON_MD_TOKEN;
}

static int remaining_file_pointer_length(FILE * fp)
{
    long int current_file_pointer_position = ftell(fp);
    fseek(fp, 0, SEEK_END);
    long int file_pointer_end_position = ftell(fp);
    fseek(fp, current_file_pointer_position, SEEK_SET);
    return file_pointer_end_position - current_file_pointer_position;

}

static char * peek_type(FILE * fp, char type, char * token_accumilator)
{
    int i = 1;
    char c;
    token_accumilator[0] = type;
    while((c = (char)fgetc(fp)) == type) {
        token_accumilator[i] = type;
        ++i;
    }
    ungetc(c, fp);
    token_accumilator[i] = '\0';

    return token_accumilator;
}

static char * peek_chars(FILE * fp, char base_char, char * token_accumilator)
{
    int i = 1, IS_CHAR = 1;
    token_accumilator[0] = base_char;

    while(IS_CHAR == 1) {
        int c = fgetc(fp);
        if(c == EOF) {
            break;
        }

        if(is_md_token((char)c) != IS_NON_MD_TOKEN) {
            IS_CHAR = 0;
            ungetc(c,fp);
        } else {
            token_accumilator[i] = c;
            ++i;
        }
    }
    token_accumilator[i] = '\0';
    return token_accumilator;
}
