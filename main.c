#include <stdio.h>
#include <stdbool.h>
#include "src/lexer.h"
#include "src/parser.h"

int main(int argc, char *argv[])
{
    char * file_name;
    char output_file_name[] = "some_file.md";
    if(!(file_name = argv[1])) {
        return 0;
    }

    int i;
    Lexer *lexer = lex_file(file_name);
    parse(lexer, output_file_name);



    return 1;
}


