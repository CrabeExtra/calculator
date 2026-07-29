#include <windows.h>

#include "ui.hpp"
#include "grid.hpp"
#include "log.hpp"
#include "theme.hpp"

/**
 * Builds the layout of the calculator. Keep in mind that duplicate ID fields will result in missing IDs in the map and therefore no re-renders.
 */
void UI::buildCalculatorLayout(std::vector<std::unordered_map<std::string, Grid*>>& rootGrids, Display& display, Calculator calc) { // (calc is short for calculator, just using slang.)
    
    rootGrids.emplace_back(); // create an empty map at the first index.

    auto& map = rootGrids.back(); // get the reference to the map.

    Grid* rootGrid = new Grid({
        .id = "root",
        .size = {
            .width = std::to_string(Window::WINDOW_WIDTH - 17) + "px",
            .height = std::to_string(Window::WINDOW_HEIGHT - 40.5) + "px"
        }
    });
    
    map.emplace(rootGrid->getId(), rootGrid); // add each of my new grids to the map. (or at least those we plan on re-rendering. I'm going to add all for now for the sake of simplicity.)

    buildCalculatorGui(rootGrid, map, display, calc);
    
}

