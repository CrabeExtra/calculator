#include <windows.h>

#include "display.hpp"
#include "grid.hpp"
#include "window.hpp"
#include "log.hpp"
#include "theme.hpp"

Grid* Display::buildCalculatorLayout() {
    Grid* rootGrid = new Grid(
        "root",
        std::to_string(Window::WINDOW_WIDTH - 17),
        std::to_string(Window::WINDOW_HEIGHT - 40.5),
        Theme::Background, // background colour
        Theme::Background, // border colour
        "Root Grid", // text
        std::nullopt, // border radius width
        std::nullopt, // border radius height
        std::vector<float>{ 0.5f, 0.5f },
        nullptr // parent
    );

    Grid* row1 = new Grid(
        "row1",
        "100%",
        "110px",
        std::nullopt, // background colour
        std::nullopt, // border colour
        "Row 1", // text
        std::nullopt, // border radius width
        std::nullopt, // border radius height
        std::vector<float>{ 0.5f, 0.5f },
        rootGrid // parent
    );

    row1->addElement({
        ElementShape::Rectangle,
        {10.0f, 10.0f, 110.0f, 110.0f}, // dimensions (left, top, right, bottom, radiusX, radiusY)
        row1,
        "Test", // text
        0x888888, // background colour
        0xFFFFFF // border colour
    });

    row1->addElement({
        ElementShape::Rectangle,
        {10.0f, 10.0f, 110.0f, 110.0f}, // dimensions (left, top, right, bottom, radiusX, radiusY)
        row1,
        "Test2", // text
        0xFFFFFF, // background colour
        0xFFFFFF // border colour
    });

    Grid* row2 = new Grid(
        "row2",
        "100%",
        "100px",
        std::nullopt, // background colour
        std::nullopt, // border colour
        "Row 2", // text
        std::nullopt, // border radius width
        std::nullopt, // border radius height
        std::vector<float>{ 0.5f, 0.5f },
        rootGrid // parent
    );
    
    row2->addElement({
        ElementShape::Rectangle,
        {10.0f, 10.0f, 110.0f, 110.0f}, // dimensions (left, top, right, bottom, radiusX, radiusY)
        row2,
        "row 2 elem", // text
        0x000055, // background colour
        0xFFFFFF // border colour
    });

    return rootGrid;
}

void Display::drawGrid(const Grid& g, Window& window) {

    // Draw grid itself
    std::vector<float> coords = g.getCoordinates();

    window.rectangle(coords[0], coords[1], coords[0] + g.getWidthPx(), coords[1] + g.getHeightPx(), g.getBackgroundColor(), g.getBorderColor());
    
    // Draw each grid element. (columns)
    for (auto& elem : g.getElements()) {
        switch(elem.shape) {
            case ElementShape::Rectangle:
                window.rectangle(elem.dimensions[0], elem.dimensions[1], elem.dimensions[2], elem.dimensions[3], elem.background_color, elem.border_color);
                break;
            case ElementShape::RoundedRectangle:
                window.roundedRectangle(elem.dimensions[0], elem.dimensions[1], elem.dimensions[2], elem.dimensions[3], elem.dimensions[4], elem.dimensions[5], elem.background_color, elem.border_color);
                break;
            case ElementShape::Ellipse:
                window.ellipse(elem.dimensions[0], elem.dimensions[1], elem.dimensions[2], elem.dimensions[3], elem.background_color, elem.border_color);
                break;
            case ElementShape::Circle:
                window.ellipse(elem.dimensions[0], elem.dimensions[1], elem.dimensions[2], elem.dimensions[2], elem.background_color, elem.border_color);
                break;
        }
    }
    
    // recurse and draw each nested grid. (rows)
    for (auto& nestedRow : g.getRows()) {
        drawGrid(*nestedRow, window);
    }
}