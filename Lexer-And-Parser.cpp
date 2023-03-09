#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class TokenType {
    STRING,
    LPAREN,
    RPAREN,
    PRINT,
    SEMICOLON,
    EOF_
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(std::istream& input) : input(input), line(1), position(0) {}

    Token getNextToken() {
        skipWhiteSpace();
        if (position >= lineBuffer.size()) {
            if (!readLine()) {
                return { TokenType::EOF_, "" };
            }
        }

        char currentChar = lineBuffer[position];
        if (currentChar == '(') {
            position++;
            return { TokenType::LPAREN, "(" };
        }
        else if (currentChar == ')') {
            position++;
            return { TokenType::RPAREN, ")" };
        }
        else if (lineBuffer.substr(position, 5) == "Print") {
            position += 5;
            return { TokenType::PRINT, "print" };
        }
        else if (currentChar == '"') {
            return { TokenType::STRING, parseString() };
        }
        else if (currentChar == ';') {
            position++;
            return { TokenType::SEMICOLON, ";" };
        }
        else {
            return { TokenType::STRING, parseIdentifier() };
        }
    }

private:
    std::istream& input;
    std::string lineBuffer;
    int line;
    int position;

    void skipWhiteSpace() {
        while (position < lineBuffer.size() && std::isspace(lineBuffer[position])) {
            position++;
        }
    }

    bool readLine() {
        std::getline(input, lineBuffer);
        if (input.fail()) {
            return false;
        }
        position = 0;
        line++;
        return true;
    }

    std::string parseString() {
        std::string value = "";
        position++;  // Skip opening quote
        while (position < lineBuffer.size()) {
            char currentChar = lineBuffer[position];
            if (currentChar == '"') {
                position++;
                return value;
            }
            else {
                value += currentChar;
                position++;
            }
        }
        throw std::runtime_error("Unclosed string literal");
    }

    std::string parseIdentifier() {
        std::string value = "";
        while (position < lineBuffer.size()) {
            char currentChar = lineBuffer[position];
            if (currentChar == '(' || currentChar == ')' || currentChar == ';' || currentChar == ' ' || currentChar == '"') {
                return value;
            }
            else {
                value += currentChar;
                position++;
            }
        }
        return value;
    }
};

class Parser {
public:
    Parser(std::vector<Token> tokens) : tokens(tokens), position(0) {}

    void parse() {
        while (position < tokens.size()) {
            parseCommand();
            position++;
        }
    }

private:
    std::vector<Token> tokens;
    int position;

    void parseCommand() {
        Token token = getNextToken();
        if (token.type == TokenType::PRINT) {
            parsePrintStatement();
        }
    }

    void parsePrintStatement() {
        Token token = getNextToken();
        if (token.type != TokenType::LPAREN) {
            throw std::runtime_error("Expected '('");
        }

        token = getNextToken();
        if (token.type != TokenType::STRING) {
            throw std::runtime_error("Expected string literal");
        }
        std::cout << token.value;

        token = getNextToken();
        while (true) {
            if (token.type == TokenType::RPAREN) {
                break;
            }
            else if (token.type == TokenType::SEMICOLON) {
                std::cout << std::endl;
                return;
            }
            else {
                throw std::runtime_error("Expected ';' or ')'");
            }
            token = getNextToken();
        }
        std::cout << std::endl;
    }

    Token getNextToken() {
        if (position >= tokens.size()) {
            return { TokenType::EOF_, "" };
        }
        return tokens[position++];
    }
};



class Interpreter {
public:
    void run(std::istream& input) {
        std::vector<Token> tokens;
        Lexer lexer(input);
        Token token = lexer.getNextToken();
        while (token.type != TokenType::EOF_) {
            tokens.push_back(token);
            token = lexer.getNextToken();
        }

        Parser parser(tokens);
        parser.parse();
    }
};

int main() {
    while (true) {
        std::stringstream ss;
        std::string line;
        std::cout << "Enter program lines. Type 'Run()' on a separate line to execute program.\n";
        while (std::getline(std::cin, line)) {
            if (line == "Run();") {
                break;
            }
            ss << line << '\n';
        }
        Interpreter interpreter;
        interpreter.run(ss);
    }
    return 0;
}
