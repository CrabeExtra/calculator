#include <windows.h>

#include "display.hpp"
#include "grid.hpp"
#include "window.hpp"
#include "log.hpp"
#include "theme.hpp"

/**
 * Builds the layout of the calculator. Keep in mind that duplicate ID fields will result in missing IDs in the map and therefore no re-renders.
 */
void Display::buildCalculatorLayout(std::vector<std::unordered_map<std::string, Grid*>>& rootGrids) {
    rootGrids.emplace_back(); // create an empty map at the first index.
    auto& map = rootGrids.back(); // get the reference to the map.

    Grid* rootGrid = new Grid(
        "root",
        std::to_string(Window::WINDOW_WIDTH - 17),
        std::to_string(Window::WINDOW_HEIGHT - 40.5),
        std::nullopt,
        nullptr,
        std::nullopt,
        Theme::Background, // background colour
        Theme::Background, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(rootGrid->getId(), rootGrid); // add each of my new grids to the map. (or at least those we plan on re-rendering. I'm going to add all for now for the sake of simplicity.)

    buildCalculatorGui(rootGrid, map);
    
}

void Display::drawGrid(const Grid& g, Window& window) {

    if(g.getAbsoluteCoords().size() < 1) return;
    // Draw grid itself
    std::vector<float> coords = g.getAbsoluteCoords();

    switch(g.getBorderShape()) {
        case BorderShape::Rectangle:
            window.rectangle(coords[0], coords[1], coords[2], coords[3], g.getBackgroundColor() ? g.getBackgroundColor() : std::nullopt, g.getBorderColor());
            break;
        case BorderShape::RoundedRectangle:
            window.roundedRectangle(coords[0], coords[1], coords[2], coords[3], g.getBorderRadiusW() ? *g.getBorderRadiusW() : 0.0f, g.getBorderRadiusH() ? *g.getBorderRadiusH() : 0.0f, g.getBackgroundColor(), g.getBorderColor());
            break;
        case BorderShape::Ellipse:
            window.ellipse(coords[0], coords[1], coords[2], coords[3], g.getBackgroundColor(), g.getBorderColor());
            break;
        case BorderShape::Circle:
            window.ellipse(coords[0], coords[1], coords[2], coords[3], g.getBackgroundColor(), g.getBorderColor());
            break;
    }

    auto text = *g.getText();

    if(!text.empty()) {
        window.text(coords[0], coords[1], coords[2], coords[3], text);
    }
    
    // recurse and draw each nested grid.
    for (auto& nestedRow : g.getElements()) {
        drawGrid(*nestedRow, window);
    }
}