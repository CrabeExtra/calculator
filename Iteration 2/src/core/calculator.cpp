#include <algorithm>
#include <vector>
#include <cmath>

#include "calculator.hpp"
#include "log.hpp"

double Calculator::add(double a, double b) {
    return a + b;
}

double Calculator::subtract(double a, double b) {
    return a - b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

double Calculator::divide(double a, double b) {
    return a / b;
}

// can make this public Calc functions and the str and char funcs pvt of the same.
double modulus(double a, double b) {
    return std::fmod(a, b);
}

bool isCharOperator(char c) { return c == '+' || c == '-' || c == '÷' || c == 'x' || c == '%' || c == '/'; }

bool isStrOperator(std::string str) { return str.size() == 1 && (isCharOperator(str[0]) || str == "÷"); }

double Calculator::operate(double a, double b, char op) {
    switch(op) {
        case '+': 
            return add(a, b);
            break;
        case '-':
            return subtract(a, b);
            break;
        case 'x':
            return multiply(a, b);
            break;
        case '/':
            return divide(a, b);
            break;
        case '%':
            return modulus(a, b);
            break;
        default:
            return 0.0;
            break;
    }
}

// should really create a well documented library for stuff like this.

bool contains(std::vector<char>& cv, char value) {
    return std::find(cv.begin(), cv.end(), value) != cv.end();
}

bool strContains(std::string& str, char value) {
    return str.find(value) != std::string::npos;
}

bool strContainsSubStr(std::string& str, std::string& substr) {
    return str.find(substr) != std::string::npos;
}

// TODO: need to handle overflow, will also need to handle larger numbers later on.
//  TODO 2: this is inefficient. Fine for the scope of the project though. it's like O(3n). I can simplify a few things by starting at the 
//          end of the currentDisplay string and iterating backwards, pushing the terms and ops in reverse order. Then consuming them by 
//          popping the last value from the array as each next consecutive operator.
//          This prevents the inefficient shuffling by the std::erase method. There's a few more things I could do, but ultimately there is really
//          not much data crunching here so it doesn't matter that much. 
// This function is super inefficient, not a big deal because the display is pretty small. but still.
void Calculator::calculate(std::string& currentDisplay) {
    std::vector<char> ops;
    std::vector<double> terms;

    std::string currentTerm = "";

    std::string divisionSymbol = "÷";

    while(strContainsSubStr(currentDisplay, divisionSymbol)) {
        size_t i = currentDisplay.find(divisionSymbol);
        currentDisplay.replace(i, divisionSymbol.length(), "/");
    }

    // break our input into terms and operators.
    for(int i = 0; i < (int)currentDisplay.length(); i++) {
        if(isCharOperator(currentDisplay[i])) {
            if((int)currentTerm.length() > 0) {
                terms.push_back(std::stod(currentTerm));
                currentTerm = "";
            }

            ops.push_back(currentDisplay[i]);
            continue;
        }
        
        currentTerm += currentDisplay[i];
    }

    terms.push_back(std::stod(currentTerm));

    // iterate operators and calculate!
    // following bodmas, we want to do division and multiplication before adding and subtraction, keeping in mind general order of operations from left to right.
    
    // modulus, multiplications and divisions
    for(int i = 0; (int)terms.size() > 1 && (contains(ops, '%') || contains(ops, 'x') || contains(ops, '/')); i++) {
        if(ops[i] == 'x' || ops[i] == '%' || ops[i] == '/') {
            terms[i] = operate(terms[i], terms[i+1], ops[i]);
            ops.erase(ops.begin() + i);
            terms.erase(terms.begin() + i + 1);
            i--;
        }
    }

    //adding and subtracting
    // could use a while loop here but a for loop is just more convenient.
    for(int i = 0; (int)terms.size() > 1; i++) {
        terms[i] = operate(terms[i], terms[i+1], ops[i]);
        ops.erase(ops.begin() + i);
        terms.erase(terms.begin() + i + 1);
        i--;
    }

    if(terms.size() > 1) {
        Log::warning("Unexpected situation. Terms not reduced to 1.");
    }

    std::string toReturn = std::to_string(std::trunc(terms[0]*100)/100);

    while(strContains(toReturn, '.') && (toReturn[(int)toReturn.length() - 1] == '0' || toReturn[(int)toReturn.length() - 1] == '.')) {
        toReturn.pop_back();
    }

    currentDisplay = toReturn;
}

void Calculator::handleInput(std::string& input, std::string& currentDisplay) {
    if((int)currentDisplay.length() >= 13) { // approx screen size - there's currently an issue where % takes up too much width
        currentDisplay = "ERR";
        return;
    }

    if(currentDisplay == "ERR"){
        currentDisplay = "";
    }

    if(input == "DEL") {
        if((int)currentDisplay.length() == 1)
            currentDisplay = "0";
        else if((int)currentDisplay.length() > 0)
            currentDisplay.pop_back();
    }
    else if(input == "C")
        currentDisplay = "0";
    else if(input == "=")
        calculate(currentDisplay);
    else if(input == ".") {
        std::string currentTerm = "";

        for(int i = (int)currentDisplay.length() - 1; i >= 0; i--) {
            if(isCharOperator(currentDisplay[i])) {
                break;
            }

            // handle multi byte ÷ symbol:
            std::string divSym = currentDisplay.substr(i, 2);
            if(divSym == "÷") {
                break;
            }
            
            currentTerm = currentTerm + currentDisplay[i];
        }

        if(!strContains(currentTerm, '.') && (int)currentTerm.length() > 0) {
            currentDisplay += ".";
        }
    }
    else if(isStrOperator(input)) {
        if(isCharOperator(currentDisplay[(int)currentDisplay.length()-1]))
            return;
        currentDisplay += input;
    } else {
        

        if(currentDisplay != "0") {
            currentDisplay += input;
            return;
        }

        currentDisplay = input;

    }
}

