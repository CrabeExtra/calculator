#include <windows.h>

#include "display.hpp"
#include "layout/grid.hpp"
#include "platform/window.hpp"

Grid buildCalculatorLayout() {
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

void drawGrid(const Grid& g, Window& window){
    for (auto& rect : g.rects)
        window.rectangle(...);

    for (auto& child : g.children)
        drawGrid(child, window);
}