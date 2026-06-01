#pragma once

#include <string>
#include <optional>
#include <vector>

enum class ElementShape {
    Rectangle,
    RoundedRectangle,
    Ellipse,
    Circle
};

struct GridElement {
    ElementShape shape;
    std::vector<float> dimensions;
    std::optional<std::string> text;
    std::optional<uint32_t> background_color;
    std::optional<uint32_t> border_color;
};

class Grid {
    public:
        /**
         * rubber ducking here:
         * I'll implement this similar to an html flex grid.
         * I need to be able to create rectangles, rounded rectangles, circles, and ovals.
         * I should be able to create nested grids.
         * each grid should be able to have a background color, and a border color and width.
         * To each grid I should be able to align the content, and add text.
         * I'll just add components sequentially, that way I can calculate the position of each component based on the previous components.
         * Each instance of grid will be a row, and each component rendered by that grid will be a column.
         * functions specific to OS, like rendering, will be implemented in the OS specific code, and called from the grid class to prevent reliance on windows or linux etc.
         */
        Grid(
            std::string width,
            std::string height,
            std::optional<uint32_t> background_color,
            std::optional<uint32_t> border_color,
            std::optional<std::string> text = std::nullopt,
            std::optional<int> border_radius_width = std::nullopt,
            std::optional<int> border_radius_height = std::nullopt,
            Grid* parent = nullptr
        ) : 
            width(width),
            height(height),
            background_color(background_color),
            border_color(border_color),
            border_radius_width(border_radius_width),
            border_radius_height(border_radius_height),
            parent(parent)
        {}
        std::vector<Grid> getChildren() const { return children; }
        std::vector<GridElement> getElements() const { return elements; }

    private:
        std::string width;
        std::string height;
        std::optional<uint32_t> background_color;
        std::optional<uint32_t> border_color;
        std::optional<int> border_radius_width;
        std::optional<int> border_radius_height;
        Grid* parent;
        std::vector<Grid> children;
        std::vector<GridElement> elements;
};