#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "src/lexer.h"
#include "src/parser.h"
#include "src/utils.h"

int main(int argc, char *argv[])
{
    char * file_name;
    char * output_file;
    if(!(file_name = argv[1])) {
        return EXIT_FAILURE;
    }

    // Is the path directory?
    if (`(file_name)) {
        printf("This tool can only be used in files!\n");
        return EXIT_FAILURE;
    }

    // Ajust the extension of the file
    output_file = change_extension(file_name, ".html");

    Lexer *lexer = lex_file(file_name);
    parse(lexer, output_file);
    free(output_file);

    return EXIT_SUCCESS;
}


