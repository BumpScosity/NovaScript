#include "Parser.h"
#include <stdexcept>
#include <cmath>

Parser::Parser(Lexer& lexer)
    : m_lexer(lexer)
{
    m_current_token = m_lexer.getNextToken();
}

void Parser::eat(TokenType token_type)
{
    if (m_current_token.type == token_type) {
        m_current_token = m_lexer.getNextToken();
    } else {
        throw std::runtime_error("Unexpected token");
    }
}

double Parser::parse()
{
    double result = expression();

    if (m_current_token.type != TokenType::END_OF_INPUT) {
        throw std::runtime_error("Unexpected token");
    }

    return result;
}

double Parser::factor()
{
    Token token = m_current_token;
    double result = 0.0;

    if (token.type == TokenType::NUMBER) {
        eat(TokenType::NUMBER);
        result = std::stod(m_current_token.lexeme);
    } else if (token.type == TokenType::LEFT_PAREN) {
        eat(TokenType::LEFT_PAREN);
        result = expression();
        eat(TokenType::RIGHT_PAREN);
    } else {
        throw std::runtime_error("Unexpected token");
    }

    return result;
}

double Parser::factor2()
{
    double result = factor();

    while (m_current_token.type == TokenType::MULTIPLY ||
           m_current_token.type == TokenType::DIVIDE ||
           m_current_token.type == TokenType::MODULO) {
        Token op = m_current_token;
        if (op.type == TokenType::MULTIPLY) {
            eat(TokenType::MULTIPLY);
            result *= factor();
        } else if (op.type == TokenType::DIVIDE) {
            eat(TokenType::DIVIDE);
            result /= factor();
        } else {
            eat(TokenType::MODULO);
            result = fmod(result, factor());
        }
    }

    return result;
}

double Parser::term()
{
    double result = factor2();

    while (m_current_token.type == TokenType::PLUS ||
           m_current_token.type == TokenType::MINUS) {
        Token op = m_current_token;
        if (op.type == TokenType::PLUS) {
            eat(TokenType::PLUS);
            result += factor2();
        } else {
            eat(TokenType::MINUS);
            result -= factor2();
        }
    }

    return result;
}

double Parser::expression()
{
    return term();
}
