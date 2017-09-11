#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lexer.h"

#define STAR_PARSING 0
#define UNDERSCORE_PARSING 1
#define TILDE_PARSING 2
#define HASH_PARSING 3

static int heading_length(Token *);
static char * parse_star(Token *, int);

void parse(Lexer * lexer, char * input_file_name)
{
    size_t length = lexer->token_count * sizeof(Token);
    char file_string[length];
    int parse_active_table[4];
    int current_parse_heading_length;
    memset(file_string, 0, length);

    for(int i = 0; i < lexer->token_count; ++i) {
        Token * token = lexer->tokens[i];
        if(strcmp(token->type, "char_string") == 0) {

            strncat(file_string, token->cargo, strlen(token->cargo) +1);

        } else if(strcmp(token->type, "blank_line") == 0) {

            char tag[10];
            if(parse_active_table[HASH_PARSING] == HASH_PARSING) {
                sprintf(tag, "</h%d>", current_parse_heading_length);
            }
            strncat(tag, "<br>\n", 5);
            strncat(file_string, tag, strlen(tag) +1);
        } else if(strcmp(token->type, "heading") == 0) {

            char tag[5];
            int header_length = heading_length(token);

            sprintf(tag, "<h%d>", header_length);
            parse_active_table[HASH_PARSING] = HASH_PARSING;
            strncat(file_string, tag, strlen(tag) +1);
            current_parse_heading_length = header_length;

        } else if(strcmp(token->type, "star") == 0) {
            char * tag;

            if(parse_active_table[STAR_PARSING] == STAR_PARSING) {

                tag = parse_star(token, 1);
                strncat(file_string, tag, strlen(tag) +1);
                parse_active_table[STAR_PARSING] = -1;

            } else {

                tag = parse_star(token, 0);
                strncat(file_string, tag, strlen(tag) +1);
                parse_active_table[STAR_PARSING] = STAR_PARSING;

            }
        } else if(strcmp(token->type, "tilde") == 0) {

            if(parse_active_table[TILDE_PARSING] == TILDE_PARSING) {
                strncat(file_string, "</code>", 7);
            } else {
                strncat(file_string, "<code>", 6);
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

static char * parse_star(Token * token, int is_closing_tag)
{
    int star_length = strlen(token->cargo);
    char * tag = malloc(5);
    if(is_closing_tag == 1) {
        switch(star_length) {
            case 1:
                tag = "</i>";
                break;
            case 2:
                tag = "</b>";
                break;
            }
    } else {
        switch(star_length) {
            case 1:
            tag = "<i>";
            break;
        case 2:
            tag = "<b>";
            break;
        }
    }

    return tag;

}
