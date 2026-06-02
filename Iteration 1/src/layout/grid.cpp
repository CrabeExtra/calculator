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
void Grid::addElement(GridElement element) {
    
    // alter dimensions.
    std::vector<float> pCoords = element.parent->getCoordinates();
    std::vector<GridElement> elementsInThisRow = element.parent->getElements();

    float elemWidth = element.getWidth();
    float elemHeight = element.getHeight();

    if(elementsInThisRow.empty()) {
        // can set starting coords to same as parents.
        element.dimensions[0] = pCoords[0] + element.dimensions[0];
        element.dimensions[2] = element.dimensions[0] + elemWidth;

        element.dimensions[1] = pCoords[1] + element.dimensions[1];
        element.dimensions[3] = element.dimensions[1] + elemHeight;
    } else {
        GridElement prevElem = elementsInThisRow[elementsInThisRow.size() - 1];
        element.dimensions[0] = prevElem.dimensions[2] + element.dimensions[0];
        element.dimensions[2] = element.dimensions[0] + elemWidth;

        element.dimensions[1] = pCoords[1] + element.dimensions[1];
        element.dimensions[3] = element.dimensions[1] + elemHeight;
    }

    elements.push_back(element);
}
// TODO: handle case where a row sits in an element rather than another row? should I give row an enum property that lets it be a column or a row? hmm. 

void Grid::addRow(Grid* row) {
    std::vector<float> coords = row->getCoordinates();
    std::vector<Grid*> rowsInThisContainer = row->parent->getRows();
    std::vector<float> parentCoords = row->parent->getCoordinates();

    if(rowsInThisContainer.empty()) {
        coords[0] = coords[0] + parentCoords[0];
        coords[1] = coords[1] + parentCoords[1];
    } else {
        Grid* latestRow = rowsInThisContainer[rowsInThisContainer.size() - 1];
        std::vector<float> latestRowCoords = latestRow->getCoordinates();

        float latestRowHeight = latestRow->getHeightPx();

        coords[0] = coords[0] + latestRowCoords[0];
        coords[1] = coords[1] + latestRowCoords[1] + latestRowHeight;
    }   

    row->setCoords(coords);
    
    rows.push_back(row);
}