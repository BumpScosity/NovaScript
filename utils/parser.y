%{
#include <stdio.h>
#include <stdlib.h>
#include <parser.tab.h>
extern int yylex();
extern void yyerror(const char *s);
%}

%union {
    char *sval;
}

%token <sval> STRING
%token PRINT SEMICOLON
%token LPAREN RPAREN
%token UNKNOWN

%%

program:
    statements
    ;

statements:
    statement
    | statements statement
    ;

statement:
    PRINT LPAREN STRING RPAREN SEMICOLON { printf("Print: %s\n", $3); free($3); }
    ;

%%
