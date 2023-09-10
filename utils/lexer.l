%{
#include <parser.tab.h>
%}

%%

[ \t\r]+       /* Ignore whitespace */
"//".*         /* Ignore single-line comments */
"printf"       { return PRINT; }
\"[^\n\"]+\"  { yylval.sval = strdup(yytext); return STRING; }
";"           { return SEMICOLON; }
"("         { return LPAREN; }
")"         { return RPAREN; }
.             { return UNKNOWN; }

%%

int yywrap() {
return 1;
}
