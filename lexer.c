#include <stdio.h>
#include <stdbool.h>

#define TOKEN_COUNT 3

bool is_md_token(char*);

char * md_tokens[TOKEN_COUNT] = {
    "#", "=", "-"
};

void lex_file(char * file_name)
{
    FILE *fp = fopen(file_name, "r");
    int i = 0;
    size_t char_count;
    fseek(fp, 0, SEEK_END);
    char_count = ftell(fp);
    rewind(fp);


    while(i < char_count) {
        char curr_token;
        curr_token = (char)fgetc(fp);
        if(is_md_token(&curr_token)) {
            switch(curr_token) {
                case '#':

                case '=':

                case '-':
                    break;
            }
        }

        ++i;
    }
    return;
}

bool is_md_token(char * token)
{
    int i;
    for(i = 0; i < TOKEN_COUNT-1; ++i) {
        if(token == md_tokens[i]) {
            return true;
        }
    }
    return false;
}


