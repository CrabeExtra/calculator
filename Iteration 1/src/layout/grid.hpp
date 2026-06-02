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

static std::string getElementName(ElementShape es) {
    switch(es) {
        case ElementShape::Rectangle:
            return "Rectangle";
        break;
        case ElementShape::RoundedRectangle:
            return "RoundedRectangle";
        break;
        case ElementShape::Ellipse:
            return "Ellipse";
        break;
        case ElementShape::Circle:
            return "Circle";
        break;
    }
}

class Grid; // forward declaration to ensure type exists for GridElement type.

struct GridElement {
    ElementShape shape;
    std::vector<float> dimensions;
    Grid* parent;
    std::optional<std::string> text;
    std::optional<uint32_t> background_color;
    std::optional<uint32_t> border_color;
    std::optional<std::vector<Grid>> columns;

    inline float getWidth() const { return dimensions[2] - dimensions[0]; } // TODO: account for if these are elliptical.
    inline float getHeight() const { return dimensions[3] - dimensions[1]; }
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
            std::string id,
            std::string width,
            std::string height,
            std::optional<uint32_t> background_color,
            std::optional<uint32_t> border_color,
            std::optional<std::string> text = std::nullopt,
            std::optional<int> border_radius_width = std::nullopt,
            std::optional<int> border_radius_height = std::nullopt,
            std::vector<float> coordinates = std::vector<float> { 0.0f, 0.0f},
            Grid* parent = nullptr
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
        std::vector<Grid*> getRows() const { return rows; }
        std::vector<GridElement> getElements() const { return elements; }
        std::optional<uint32_t> getBackgroundColor() const { return background_color; }
        std::optional<uint32_t> getBorderColor() const { return border_color; }
        std::optional<std::string> getText() const { return text; }
        Grid* getParent() const { return parent; }
        float getWidthPx() const;
        float getHeightPx() const;
        float strToWidthPx(std::string str, std::optional<float> parentWidth) const;
        float strToHeightPx(std::string str, std::optional<float> parentHeight) const;
        std::vector<float> getCoordinates() const { return coordinates; };
        void setWidth(std::string _width) { width = _width; }
        void setHeight(std::string _height) { height = _height; }
        void setCoords(std::vector<float> _coordinates) { coordinates = _coordinates; };
        void addElement(GridElement element);
        void addRow(Grid* row);

    private:
        std::string id;
        std::string width;
        std::string height;
        std::vector<float> coordinates;
        std::optional<std::string> text;
        std::optional<uint32_t> background_color;
        std::optional<uint32_t> border_color;
        std::optional<int> border_radius_width;
        std::optional<int> border_radius_height;
        Grid* parent;
        std::vector<Grid*> rows = std::vector<Grid*>{};
        std::vector<GridElement> elements = std::vector<GridElement>{};
};