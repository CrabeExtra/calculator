#pragma once

#include <string>
#include "grid.hpp"
#include "calculator.hpp"
#include "display.hpp"

/**
 * This is pretty basic to be honest. I'll think of more uses for this later on. At the moment though 
 * it kind of just represents 'what will be visible on the calculator screen'.
 * 
 */
class UI
{
    public:
        void buildCalculatorLayout(std::vector<std::unordered_map<std::string, Grid*>>& rootGrids, Display& display, Calculator calc);
        void buildCalculatorGui(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Display& display, Calculator calc);
        void buildCalculatorScreen(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Display& display);
        void buildCalculatorButtons(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Display& display, Calculator calc);
};