#include <stdio.h>
#include <stdbool.h>
#include "lexer.h"

void lex_file(char*);

int main(int argc, char *argv[])
{
    char * file_name;
    if(!(file_name = argv[1])) {
        return 0;
    }

    lex_file(file_name);
    return 1;
}


