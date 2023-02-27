#include <iostream>
#include <string>
#include "Lexer.h"
#include "Parser.h"

int main()
{
    std::string input;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, input);

    Lexer lexer(input);
    Parser parser(lexer);

    try {
        double result = parser.parse();
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "Press enter to exit...";
    std::cin.ignore();
    return 0;
}
