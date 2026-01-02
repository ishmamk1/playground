#include "calculator.h"
#include <iostream>

int main() {
    double x, y, answer;
    char operand;

    std::cout << "Enter expression in format (x + y): \n";
    std::cin >> x >> operand >> y;

    switch (operand)
    {
    case '+':
        answer = add(x,y);
        break;
    case '-':
        answer = subtract(x,y);
        break;
    case '*':
        answer = multiply(x,y);
        break;
    case '/':
        answer = divide(x,y);
        break;
    default:
        std::cerr << "Invalid operand\n";
        return 1;
    }
    std::cout << "Answer is: " << answer << std::endl;
}