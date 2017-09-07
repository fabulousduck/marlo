#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static int heading_length(Token *);

void parse(Lexer * lexer, char * input_file_name)
{
    printf("starting file parsing %s\n", input_file_name);
    char file_string[100];
    int i;
    memset(file_string, 0, 100);
    printf("file name :%s <<",input_file_name);

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
                strncat(file_string, heading_string, strlen(heading_string));
            }
        } else if(strcmp(token->type, blank_line) == 0) {
            strncat(file_string, "<br>\n", 5);
        }
    }
/*    char *e;
    int index;
    e = strchr(input_file_name, '.');
    index = (int)(e - input_file_name);
    printf("index : %d\n", index);
    input_file_name[index] = 'h';
    input_file_name[index+1] = 't';
    strncat(input_file_name, "ml", 2);

    printf("file name: %s\n", input_file_name);
 */   return;
}

static int heading_length(Token * token)
{
    return strlen(token->cargo);
}
