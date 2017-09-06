#include <stdio.h>
#include <stdbool.h>
#include "src/lexer.h"


int main(int argc, char *argv[])
{
    char * file_name;
    if(!(file_name = argv[1])) {
        return 0;
    }

    int i;
    Lexer *lexer = lex_file(file_name);
    for(i = 0; i < 100000; ++i) {

    }
    printf("%ld\n", lexer->token_count);
    for(i = 0; i < lexer->token_count; ++i) {
        printf("token_size %d\n", lexer->tokens[i]->size);
        printf("token: %s\n", lexer->tokens[i]->cargo);
    }


    return 1;
}


