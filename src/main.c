#include <stdio.h>
#include <stdlib.h>
#include <parser.tab.h>

extern int yyparse();
extern FILE* yyin; // Define yyin

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *inputFileName = argv[1];
    FILE *inputFile = fopen(inputFileName, "r");

    if (!inputFile) {
        fprintf(stderr, "Error: Unable to open input file '%s'\n", inputFileName);
        return 1;
    }

    yyin = inputFile; // Set Flex's input file

    yyparse();

    fclose(inputFile);

    return 0;
}
