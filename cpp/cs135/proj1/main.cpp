#include <iostream>
#include <string>
#include <cmath>

// Task A
/*
int main() {
    int sum = 0, num;
    while (std::cin >> num) {
        sum += num;
    }
    std::cout << sum << std::endl;
    return 0;
}
*/

// Task B
/*
int main() {
    int total = 0, num = 0, operand = 1;
    char curr;

    while (std::cin >> curr) {
        if (isdigit(curr)) {
            num *= 10;
            num += curr - '0';
        } else {
            total = (operand) ? total + num : total - num;
            num = 0;
            operand = (curr == '+') ? 1 : 0;
        }
    }
    total = (operand) ? total + num : total - num;
    std::cout << total << std::endl;
    return 0;
}
*/

// Task C

/*
int main() {
    int total = 0, num = 0, operand = 1;
    char curr;

    while (std::cin >> curr) {
        if (isdigit(curr)) {
            num *= 10;
            num += curr - '0';
        } else {
            total = (operand) ? total + num : total - num;
            num = 0;
            if (curr == ';') {
                std::cout << total << std::endl; 
                total = 0;
            }
            else operand = (curr == '+') ? 1 : 0;
        } 
    }
    return 0;
}
*/

// Task D
int main() {
    int total = 0, num = 0, operand = 1;
    char curr;

    while (std::cin >> curr) {
        if (isdigit(curr)) {
            num *= 10;
            num += curr - '0';
        } else if (curr == '^') {
            num = pow(num, 2);
        } else {
            total = (operand) ? total + num : total - num;
            num = 0;
            if (curr == ';') {
                std::cout << total << std::endl; 
                total = 0;
            }
            else operand = (curr == '+') ? 1 : 0;
        } 
    }
    return 0;
}
