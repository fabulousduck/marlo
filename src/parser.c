#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static int heading_length(Token *);

void parse(Lexer * lexer, char * input_file_name)
{
    size_t length = lexer->token_count * sizeof(Token);
    char file_string[length];
    memset(file_string, 0, length);

    for(int i = 0; i < lexer->token_count; ++i) {
        Token * token = lexer->tokens[i];

        if(strcmp(token->type, "char_string") == 0) {
            if(strcmp(lexer->tokens[i - 1]->type, "heading") == 0) {
                int header_length = heading_length(lexer->tokens[i - 1]);
                char heading_string[strlen(token->cargo) + 5];
                sprintf(heading_string, "<h%d>%s\n", header_length, token->cargo);
                strncat(file_string, heading_string, strlen(heading_string));
            }
        } else if(strcmp(token->type, "blank_line") == 0) {
            strncat(file_string, "<br>\n", 5);
        }
    }

    FILE * markdown_file;
    if ((markdown_file = fopen(input_file_name, "wr"))) {
        fprintf(markdown_file, "%s", file_string);
        fclose(markdown_file);
    } else {
        perror("failed to create markdown file. Exiting\n");
    }
    return;
}

static int heading_length(Token * token)
{
    return strlen(token->cargo);
}
