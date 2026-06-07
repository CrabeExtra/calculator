#pragma once

#include <string>
#include <optional>
#include <vector>

#include "theme.hpp"

enum class BorderShape {
    Rectangle,
    RoundedRectangle,
    Ellipse,
    Circle
};

enum class GridDirection {
    Row,
    Col
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
            std::string id = "",
            std::string width = "100%",
            std::string height = "100%",
            std::vector<float> coordinates = std::vector<float> { 0.0f, 0.0f},
            Grid* parent = nullptr,
            std::optional<uint32_t> background_color = NULL, // TODO: create specific structs for the styling, positioning, etc.
            std::optional<uint32_t> border_color = NULL,
            std::optional<std::string> text = std::nullopt,
            std::optional<BorderShape> borderShape = BorderShape::Rectangle,
            std::optional<int> border_radius_width = std::nullopt,
            std::optional<int> border_radius_height = std::nullopt
        ) : 
            id(id),
            width(width),
            height(height),
            background_color(background_color),
            border_color(border_color),
            text(text),
            border_radius_width(border_radius_width),
            border_radius_height(border_radius_height),
            parent(parent),
            coordinates(coordinates)
        {
            if(parent)
                parent->addRow(this); // just prevents having to add explicitly
        }

        // getters
        std::vector<float> getCoordinates() const { return coordinates; };
        std::vector<float>& getAbsoluteCoords() { return absoluteCoordinates; };
        std::vector<Grid*> getElements() const { return elements; }
        std::optional<uint32_t> getBackgroundColor() const { return background_color; }
        std::optional<uint32_t> getBorderColor() const { return border_color; }
        std::optional<std::string> getText() const { return text; }
        BorderShape getBorderShape() const { return borderShape; }
        Grid* getParent() const { return parent; }
        float getWidthPx() const;
        float getHeightPx() const;

        // setters
        void setWidth(std::string _width) { width = _width; }
        void setHeight(std::string _height) { height = _height; }
        void setAbsoluteCoords (std::vector<float> _coordinates) { absoluteCoordinates = _coordinates; };

        // structural
        void addCol(Grid* col);
        void addRow(Grid* row);

        // helpers
        float strToWidthPx(std::string str, std::optional<float> parentWidth) const;
        float strToHeightPx(std::string str, std::optional<float> parentHeight) const;

    private:
        // for referencing - efficient rendering.
        std::string id;

        // dimensions
        std::string width;
        std::string height;
        std::vector<float> coordinates;
        std::vector<float> absoluteCoordinates;

        // styling
        std::optional<std::string> text;
        std::optional<uint32_t> background_color;
        std::optional<uint32_t> border_color;
        std::optional<int> border_radius_width;
        std::optional<int> border_radius_height;
        BorderShape borderShape;
        GridDirection gridDirection;

        // structure
        Grid* parent;
        std::vector<Grid*> elements = std::vector<Grid*>{};
};