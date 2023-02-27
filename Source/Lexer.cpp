#include "Lexer.h"
#include <cctype>

Lexer::Lexer(const std::string& input)
    : m_input(input), m_position(0), m_line(1)
{
}

char Lexer::peek() {
    if (m_position >= static_cast<int>(m_input.size())) {
        return '\0';
    }
    return m_input[m_position];
}

char Lexer::consume()
{
    char c = peek();
    ++m_position;
    if (c == '\n') {
        ++m_line;
    }
    return c;
}

bool Lexer::isDigit(char c)
{
    return std::isdigit(static_cast<unsigned char>(c));
}

bool Lexer::isWhitespace(char c)
{
    return std::isspace(static_cast<unsigned char>(c));
}

Token Lexer::getNextToken()
{
    char current_char = peek();

    while (std::isspace(current_char)) {
        consume();
        current_char = peek();
    }

    if (std::isdigit(current_char)) {
        return number();
    } else if (current_char == '+') {
        consume();
        return Token(TokenType::PLUS);
    } else if (current_char == '-') {
        consume();
        return Token(TokenType::MINUS);
    } else if (current_char == '*') {
        consume();
        return Token(TokenType::MULTIPLY);
    } else if (current_char == '/') {
        consume();
        return Token(TokenType::DIVIDE);
    } else if (current_char == '%') {
        consume();
        return Token(TokenType::MODULO);
    } else if (current_char == '(') {
        consume();
        return Token(TokenType::LEFT_PAREN);
    } else if (current_char == ')') {
        consume();
        return Token(TokenType::RIGHT_PAREN);
    } else if (current_char == '\0') {
        return Token(TokenType::END_OF_INPUT);
    } else {
        std::string message = "Unexpected character: ";
        message += current_char;
        throw std::runtime_error(message);
    }
}


