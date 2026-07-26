#pragma once

#include <string>

/**
 * Basic calculator functions, as this is iteration 1, I will implement these simply. But
 * further along I want to look at handling large numbers, sorting decimal based language errors
 * due to decimal approximations, managing overflow.
 * 
 * 30/05/2026
 */
class Calculator {
    public:
        // add two doubles.
        double add(double a, double b);
        // subtract double type params -> param a from param b respectively.
        double subtract(double a, double b);
        // multiply two doubles
        double multiply(double a, double b);
        // divide double params -> param a divided by param b respectively.
        double divide(double a, double b);
        double operate(double a, double b, char op);
        void calculate(std::string& currentDisplay);
        void handleInput(std::string& input, std::string& currentDisplay); 
};