#include <stdio.h>
#include <stdarg.h>

void yyerror(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}
