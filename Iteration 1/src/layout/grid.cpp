#include "grid.hpp"
#include "log.hpp"

// TODO: this is a bit inefficient, it has to check ALL levels of hierarchy to get the width and height in pixels every time.

float Grid::getWidthPx() const {
    Grid* parent = this->getParent();
    
    return strToWidthPx( 
        this->width, 
        parent ? parent->getWidthPx() : std::optional<float>{}
    );

}

float Grid::getHeightPx() const {
    Grid* parent = this->getParent();
    
    return strToHeightPx( 
        this->height, 
        parent ? parent->getHeightPx() : std::optional<float>{}
    );
}

float Grid::strToWidthPx(std::string str, std::optional<float> parentWidth) const {
    size_t len = str.size();

    if(str[len - 1] == '%') {
        float percentage = std::stof(str.substr(0, len-1));
        
        if(!parentWidth) return 0;

        return percentage * *parentWidth / 100;
    } else if(str.substr(len - 2, 2) == "px") {
        str = str.substr(0, len - 2);
    }

    return std::stof(str);
}

float Grid::strToHeightPx(std::string str, std::optional<float> parentHeight) const {
    size_t len = str.size();

    if(str[len - 1] == '%') {
        float percentage = std::stof(str.substr(0, len-1));
        
        if(!parentHeight) return 0;

        return percentage * *parentHeight / 100;
    } else if(str.substr(len - 2, 2) == "px") {
        str = str.substr(0, len - 2);
    }
    
    return std::stof(str);
}

// TODO: think about overflow.
void Grid::addCol(Grid* col) {
    
    // alter dimensions.
    std::vector<float> coords = col->getCoordinates();
    std::vector<float> absoluteCoords = col->getAbsoluteCoords();
    std::vector<Grid*> elementsInThisContainer = col->parent->getElements();
    std::vector<float> parentCoords = col->parent->getAbsoluteCoords();

    float width = col->getWidthPx();
    float height = col->getHeightPx();

    if(elementsInThisContainer.empty()) {
        // can set starting coords to same as parents.
        absoluteCoords[0] = coords[0] + parentCoords[0];
        absoluteCoords[2] = coords[0] + width;

        absoluteCoords[1] = coords[1] + parentCoords[1];
        absoluteCoords[3] = coords[1] + height;
    } else {
        Grid* latestElement = elementsInThisContainer[elementsInThisContainer.size() - 1];
        std::vector<float> latestElemCoords = latestElement->getAbsoluteCoords();

        absoluteCoords[0] = latestElemCoords[2] + coords[0];
        absoluteCoords[2] = coords[0] + width;

        absoluteCoords[1] = parentCoords[1] + coords[1];
        absoluteCoords[3] = coords[1] + height;
    }

    elementsInThisContainer.push_back(col);
}

void Grid::addRow(Grid* row) {
    std::vector<float> coords = row->getCoordinates();
    std::vector<float> absoluteCoords = row->getAbsoluteCoords();
    std::vector<Grid*> elementsInThisContainer = row->parent->getElements();
    std::vector<float> parentCoords = row->parent->getAbsoluteCoords();

    if(elementsInThisContainer.empty()) {
        absoluteCoords[0] = coords[0] + parentCoords[0];
        absoluteCoords[1] = coords[1] + parentCoords[1];
    } else {
        Grid* latestElement = elementsInThisContainer[elementsInThisContainer.size() - 1];
        std::vector<float> latestRowCoords = latestElement->getAbsoluteCoords();

        float latestRowHeight = latestElement->getHeightPx();

        absoluteCoords[0] = coords[0] + latestRowCoords[0];
        absoluteCoords[1] = coords[1] + latestRowCoords[1] + latestRowHeight;
    }   
    
    elementsInThisContainer.push_back(row);
}