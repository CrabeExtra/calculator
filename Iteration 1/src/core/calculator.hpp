#pragma once

/**
 * Basic calculator functions, as this is iteration 1, I will implement these simply. But
 * further along I want to look at handling large numbers, sorting decimal based language errors
 * due to decimal approximations, managing overflow.
 * 
 * 30/05/2026
 */
class Calculator {

    // add two doubles.
    public: double add(double a, double b);
    // subtract double type params -> param a from param b respectively.
    public: double subtract(double a, double b);
    // multiply two doubles
    public: double multiply(double a, double b);
    // divide double params -> param a divided by param b respectively.
    public: double divide(double a, double b);
};