#include "calculator.h"
#include <iostream>

double add(double x, double y) {
    return x + y;
}

double subtract(double x, double y) {
    return x - y;
}

double multiply(double x, double y) {
    return x * y;
}

double divide(double x, double y) {
    if (y == 0) {
        std::cerr << "Error: Cannot divide by zero.\n";
        return 0;
    }
    return x / y;
}