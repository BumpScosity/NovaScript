#ifndef LEXER_H
#define LEXER_H

#include <string>

enum class TokenType {
    // Operators
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,

    // Brackets
    LEFT_PAREN,
    RIGHT_PAREN,

    // Literals
    NUMBER,

    // End of input
    END_OF_INPUT,

    // Error
    ERROR
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

class Lexer {
public:
    Lexer(const std::string& input);
    Token getNextToken();
private:
    std::string m_input;
    int m_position;
    int m_line;
    char peek();
    char consume();
    bool isDigit(char c);
    bool isWhitespace(char c);
};

#endif // LEXER_H
