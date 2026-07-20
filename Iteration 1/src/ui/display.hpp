#pragma once

#include <string>
#include "grid.hpp"
#include "window.hpp"
#include "calculator.hpp"

/**
 * This is pretty basic to be honest. I'll think of more uses for this later on. At the moment though 
 * it kind of just represents 'what will be visible on the calculator screen'.
 * 
 */
class Display
{
    public:
        void buildCalculatorLayout(std::vector<std::unordered_map<std::string, Grid*>>& rootGrids, Window& window, Calculator calc);
        void drawGrid(Grid& grid, Window& window);
        void buildCalculatorGui(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Window& window, Calculator calc);
        void buildCalculatorScreen(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Window& window);
        void buildCalculatorButtons(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Window& window, Calculator calc);

    private:
        std::string currentText;
};