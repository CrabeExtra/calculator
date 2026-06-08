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
        "Root Grid", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(rootGrid->getId(), rootGrid); // add each of my new grids to the map.

    Grid* row1 = new Grid(
        "top",
        "100%",
        "110px",
        std::vector<float> { 0.0f, 0.0f },
        rootGrid,
        std::nullopt,
        std::nullopt, // background colour
        std::nullopt, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    Grid* row1Col1 = new Grid(
        "row1Col1",
        "25%",
        "100%",
        std::vector<float> { 0.0f, 0.0f },
        row1,
        GridDirection::Col,
        std::nullopt,
        std::nullopt, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    Grid* row1Col2 = new Grid(
        "row1Col2",
        "50%",
        "100%",
        std::vector<float> { 0.0f, 0.0f },
        row1,
        GridDirection::Col,
        std::nullopt,
        0xFFFFFF, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    Grid* row1Col2Row1 = new Grid(
        "row1Col2Row1",
        "100%",
        "33.33%",
        std::vector<float> { 0.0f, 0.0f },
        row1Col2,
        GridDirection::Row,
        std::nullopt,
        0xFFFFFF, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    Grid* row1Col2Row2 = new Grid(
        "row1Col2Row2",
        "100%",
        "33.33%",
        std::vector<float> { 0.0f, 0.0f },
        row1Col2,
        GridDirection::Row,
        std::nullopt,
        0xFFFFFF, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(row1->getId(), row1);
}

void Display::drawGrid(const Grid& g, Window& window) {

    if(g.getAbsoluteCoords().size() < 1) return;
    // Draw grid itself
    std::vector<float> coords = g.getAbsoluteCoords();

    switch(g.getBorderShape()) {
        case BorderShape::Rectangle:
            window.rectangle(coords[0], coords[1], coords[0] + g.getWidthPx(), coords[1] + g.getHeightPx(), g.getBackgroundColor() ? g.getBackgroundColor() : std::nullopt, g.getBorderColor());
            
            break;
        case BorderShape::RoundedRectangle:
            window.roundedRectangle(coords[0], coords[1], coords[0] + g.getWidthPx(), coords[1] + g.getHeightPx(), g.getBorderRadiusW() ? *g.getBorderRadiusW() : 0.0f, g.getBorderRadiusH() ? *g.getBorderRadiusH() : 0.0f, g.getBackgroundColor(), g.getBorderColor());
            break;
        case BorderShape::Ellipse:
            window.ellipse(coords[0], coords[1], coords[0] + g.getWidthPx(), coords[1] + g.getHeightPx(), g.getBackgroundColor(), g.getBorderColor());
            break;
        case BorderShape::Circle:
            window.ellipse(coords[0], coords[1], coords[0] + g.getWidthPx(), coords[1] + g.getHeightPx(), g.getBackgroundColor(), g.getBorderColor());
            break;
    }
    
    // recurse and draw each nested grid.
    for (auto& nestedRow : g.getElements()) {
        drawGrid(*nestedRow, window);
    }
}