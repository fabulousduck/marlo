#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static int heading_length(Token *);

void parse(Lexer * lexer)
{
    printf("starting file parsing\n");
    char file_string[100];
    memset(file_string, 0, 100);

    int i;

    for(i = 0; i < lexer->token_count; ++i) {
        Token * token = lexer->tokens[i];
/*
        printf("cargo: %s\n size: %d\n type: %s\n\n",
                lexer->tokens[i]->cargo, lexer->tokens[i]->size, lexer->tokens[i]->type);
*/
        char buf[] = "char_string";
        if(strcmp(token->type, buf) == 0) {

            if(strcmp(lexer->tokens[i-1]->type, "heading") == 0) {
                int header_length= heading_length(lexer->tokens[i-1]);
                char heading_string[strlen(token->cargo) + 4];
                sprintf(heading_string, "<h%d>%s\n", header_length, token->cargo);
                strncat(file_string, heading_string, strlen(heading_string)+1);
            }
        }
    }
    printf("%s", file_string);

    return;
}

static int heading_length(Token * token)
{
    return strlen(token->cargo);
}
