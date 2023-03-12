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
    string value;
};

class Lexer {
public:
    Lexer(istream& input) : input(input), line(1), position(0) {}

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
    istream& input;
    string lineBuffer;
    int line;
    int position;

    void skipWhiteSpace() {
        while (position < lineBuffer.size() && isspace(lineBuffer[position])) {
            position++;
        }
    }

    bool readLine() {
        getline(input, lineBuffer);
        if (input.fail()) {
            return false;
        }
        position = 0;
        line++;
        return true;
    }

    string parseString() {
        string value = "";
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
        throw runtime_error("Unclosed string literal");
    }

    string parseIdentifier() {
        string value = "";
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
    Parser(vector<Token> tokens) : tokens(tokens), position(0) {}

    void parse() {
        while (position < tokens.size()) {
            parseCommand();
            position++;
        }
    }

private:
    vector<Token> tokens;
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
            throw runtime_error("Expected '('");
        }

        token = getNextToken();
        if (token.type != TokenType::STRING) {
            throw runtime_error("Expected string literal");
        }
        cout << token.value;

        token = getNextToken();
        while (true) {
            if (token.type == TokenType::RPAREN) {
                break;
            }
            else if (token.type == TokenType::SEMICOLON) {
                cout << endl;
                return;
            }
            else {
                throw runtime_error("Expected ';' or ')'");
            }
            token = getNextToken();
        }
        cout << endl;
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
    void run(istream& input) {
        vector<Token> tokens;
        Lexer lexer(input);
        Token token = lexer.getNextToken();
        while (token.type != TokenType::EOF_) {
            tokens.push_back(token);
            token = lexer.getNextToken();
        }
        system("cls");
        cout << "Enter program lines. Type 'Help();' on a separate line to get a list of commands.\n";
        Parser parser(tokens);
        parser.parse();
    }
};

bool false_ = true;
bool true_ = false;

int main() {
    cout << "Enter program lines. Type 'Help();' on a separate line to get a list of commands.\n";
    while (true) {
        stringstream ss;
        string line;
        cout << ">>>";
        while (getline(cin, line)) {
            if (line == "Run();") {
                break;
            }
            else if (line == "Help();") {
                system("cls");
                cout << "Enter program lines. Type 'Help();' on a separate line to get a list of commands.\n" << endl;
                cout << "Use semicolons at the end of each command." << endl;
                cout << "'Run()' Run the current commands." << endl;
                cout << "'Print()' Print out the input." << endl;
            }
            ss << line << '\n';
            cout << ">>>";
        }
        Interpreter interpreter;
        interpreter.run(ss);
    }
    return 0;
}
