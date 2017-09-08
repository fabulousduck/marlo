#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lexer.h"

#define STAR_PARSING 0
#define UNDERSCORE_PARSING 1
#define TILDE_PARSING 2

static int heading_length(Token *);

void parse(Lexer * lexer, char * input_file_name)
{
    size_t length = lexer->token_count * sizeof(Token);
    char file_string[length];
    int parse_active_table[3];
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
        } else if(strcmp(token->type, "star") == 0) {
            int star_length = strlen(token->cargo);
            if(parse_active_table[STAR_PARSING] == STAR_PARSING) {
                switch(star_length) {
                    case 1:
                        strncat(file_string, "</i>", 4);
                    case 2:
                        strncat(file_string, "</b>", 4);
                }
            } else {
                switch(star_length) {
                    case 1:
                        strncat(file_string, "<i>", 3);
                    case 2:
                        strncat(file_string, "<b>", 3);
                }
            }
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

