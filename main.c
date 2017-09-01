#include <stdio.h>
#include <stdbool.h>
#include "lexer.h"


int main(int argc, char *argv[])
{
    char * file_name;
    if(!(file_name = argv[1])) {
        return 0;
    }

    Lexer *lexer = lex_file(file_name);
    return 1;
}


