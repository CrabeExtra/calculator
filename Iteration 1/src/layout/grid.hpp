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

        /**
         * Params (all std::optional except container):
         * std::string id
            std::string width
            std::string height
            std::vector<float> coordinates
            Grid* container
            GridDirection gridDirection
            uint32_t background_color
            uint32_t border_color
            std::string text
            BorderShape borderShape
            float border_radius_width
            float border_radius_height
         */
        Grid(
            std::optional<std::string> id = std::nullopt,
            std::optional<std::string> width = std::nullopt,
            std::optional<std::string> height = std::nullopt,
            std::optional<std::vector<float>> coordinates = std::nullopt,
            Grid* container = nullptr,
            std::optional<GridDirection> gridDirection = std::nullopt,
            std::optional<uint32_t> background_color = std::nullopt, // TODO: create specific structs for the styling, positioning, etc.
            std::optional<uint32_t> border_color = std::nullopt,
            std::optional<std::string> text = std::nullopt,
            std::optional<BorderShape> borderShape = std::nullopt,
            std::optional<float> border_radius_width = std::nullopt,
            std::optional<float> border_radius_height = std::nullopt
        ) : 
            id(id.value_or("")),
            width(width.value_or("100%")),
            height(height.value_or("100%")),
            coordinates(coordinates.value_or(std::vector<float> { 0.0f, 0.0f})),
            container(container),
            gridDirection(gridDirection.value_or(GridDirection::Row)),
            background_color(background_color),
            border_color(border_color),
            text(text.value_or("")),
            borderShape(borderShape.value_or(BorderShape::Rectangle)),
            border_radius_width(border_radius_width.value_or(NULL)),
            border_radius_height(border_radius_height.value_or(NULL))
        {
            if(container)
                container->addElement(this); // just prevents having to add explicitly
            else {
                // no container, set absolute coords to coords.
                this->absoluteCoordinates = coordinates.value_or(std::vector<float> { 0.0f, 0.0f});
                this->absoluteCoordinates.resize(4);
                this->absoluteCoordinates[2] = this->absoluteCoordinates[0] + this->getWidthPx();
                this->absoluteCoordinates[3] = this->absoluteCoordinates[1] + this->getHeightPx();
            }
        }

        // getters
        std::string getId() const { return id; };
        std::vector<float> getCoordinates() const { return coordinates; };
        std::vector<float>& getAbsoluteCoords() { return absoluteCoordinates; };
        std::vector<float> getAbsoluteCoords() const { return absoluteCoordinates; };
        std::vector<Grid*>& getElements() { return elements; };
        const std::vector<Grid*>& getElements() const { return elements; };
        std::optional<uint32_t> getBackgroundColor() const { return background_color; };
        std::optional<uint32_t> getBorderColor() const { return border_color; };
        std::optional<std::string> getText() const { return text; };
        std::optional<float> getBorderRadiusW() const { return border_radius_width; };
        std::optional<float> getBorderRadiusH() const { return border_radius_height; };
        BorderShape getBorderShape() const { return borderShape; };
        const GridDirection& getGridDirection() const { return gridDirection; };
        Grid* getContainer() const { return container; };
        float getWidthPx() const;
        float getHeightPx() const;

        // setters (some thought with std::move versus const ref)
        void setWidth(const std::string& width) { this->width = width; }
        void setHeight(const std::string& height) { this->height = height; }
        void setAbsoluteCoords (const std::vector<float>& coordinates) { this->absoluteCoordinates = coordinates; };

        // structural
        void addElement(Grid* elem);
        void addCol(Grid* col);
        void addRow(Grid* row);

        // helpers
        float strToWidthPx(std::string str, std::optional<float> containerWidth) const;
        float strToHeightPx(std::string str, std::optional<float> containerHeight) const;

    private:
        // for referencing - efficient rendering.
        std::string id;

        // dimensions
        std::string width;
        std::string height;
        std::vector<float> coordinates;
        std::vector<float> absoluteCoordinates;

        // styling
        std::string text;
        std::optional<uint32_t> background_color;
        std::optional<uint32_t> border_color;
        float border_radius_width;
        float border_radius_height;
        BorderShape borderShape;
        GridDirection gridDirection;

        // structure
        Grid* container;
        std::vector<Grid*> elements = std::vector<Grid*>{};
};