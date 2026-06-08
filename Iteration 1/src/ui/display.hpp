#pragma once

#include <string>
#include "grid.hpp"
#include "window.hpp"

/**
 * This is pretty basic to be honest. I'll think of more uses for this later on. At the moment though 
 * it kind of just represents 'what will be visible on the calculator screen'.
 * 
 */
class Display
{
    public:
        void buildCalculatorLayout(std::vector<std::unordered_map<std::string, Grid*>>& rootGrids);
        void drawGrid(const Grid& grid, Window& window);

    private:
        std::string currentText;
};