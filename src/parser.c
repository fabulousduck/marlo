#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static int heading_length(Token *);

void parse(Lexer * lexer)
{
    printf("starting file parsing\n");
    char file_string[100];
    int i;
    memset(file_string, 0, 100);

    for(i = 0; i < lexer->token_count; ++i) {
        Token * token = lexer->tokens[i];
/*
        printf("cargo: %s\n size: %d\n type: %s\n\n",
                lexer->tokens[i]->cargo, lexer->tokens[i]->size, lexer->tokens[i]->type);
*/
        char char_string[] = "char_string";
        char blank_line[] = "blank_line";
        if(strcmp(token->type, char_string) == 0) {

            if(strcmp(lexer->tokens[i-1]->type, "heading") == 0) {
                int header_length= heading_length(lexer->tokens[i-1]);
                char heading_string[strlen(token->cargo) + 4];
                sprintf(heading_string, "<h%d>%s\n", header_length, token->cargo);
                strncat(file_string, heading_string, strlen(heading_string)+1);
            }
        } else if(strcmp(token->type, blank_line) == 0) {
            strncat(file_string, "<br>\n", 5);
        }
    }
    printf("%s", file_string);

    return;
}

static int heading_length(Token * token)
{
    return strlen(token->cargo);
}
