#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"

class Parser {
public:
    Parser(Lexer& lexer);
    double parse();

private:
    Lexer& m_lexer;
    Token m_current_token;

    void eat(TokenType token_type);
    double factor();
    double factor2();
    double term();
    double expression();
};

#endif
