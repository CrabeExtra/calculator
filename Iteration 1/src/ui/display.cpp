#include <windows.h>

#include "display.hpp"
#include "grid.hpp"
#include "window.hpp"

Grid Display::buildCalculatorLayout() {
    Grid g(
        "100%",
        "100%",
        0xFFFFFF, // background colour
        0x000000, // border colour
        std::nullopt, // text
        std::nullopt, // border radius width
        std::nullopt, // border radius height
        nullptr // parent
    );
    return g;
}

void Display::drawGrid(const Grid& g, Window& window){
    for (auto& rect : g.getElements()) {
        switch(rect.shape) {
            case ElementShape::Rectangle:
                window.rectangle(rect.dimensions[0], rect.dimensions[1], rect.dimensions[2], rect.dimensions[3], rect.background_color, rect.border_color);
                break;
            case ElementShape::RoundedRectangle:
                window.roundedRectangle(rect.dimensions[0], rect.dimensions[1], rect.dimensions[2], rect.dimensions[3], rect.dimensions[4], rect.dimensions[5], rect.background_color, rect.border_color);
                break;
            case ElementShape::Ellipse:
                window.ellipse(rect.dimensions[0], rect.dimensions[1], rect.dimensions[2], rect.dimensions[3], rect.background_color, rect.border_color);
                break;
            case ElementShape::Circle:
                window.ellipse(rect.dimensions[0], rect.dimensions[1], rect.dimensions[2], rect.dimensions[2], rect.background_color, rect.border_color);
                break;
        }
    }

    for (auto& child : g.getChildren()) {
        drawGrid(child, window);
    }
}