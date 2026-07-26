#include <queue>

#include "app.hpp"
#include "log.hpp"

Grid* App::getMouseOver(int x, int y) {
    // just assuming these already exist. Note on floating "root" text here.
    std::unordered_map<std::string, Grid *>& map = rootGrids[activeGridIndex];
    Grid* g = map["root"]; // TODO: what to do with the floating "root".

    return g->getLeafAtLocation(x, y);
    
}   

/// @brief On mouse move. On mouse move the currently hovered element will have its onMouseOver function called. While the previously hovered component (if no longer hovered) will have its onMouseOut function called.
/// @param x 
/// @param y 
void App::onMouseMove(int x, int y) {
    
    Grid* cursorGrid = getMouseOver(x, y);

    if(!cursorGrid) return;

    std::string currentId = cursorGrid->getId();
    if(currentId != getHoverId()) {
        Grid* unHoveredGrid = rootGrids[activeGridIndex][getHoverId()];
        if(unHoveredGrid && unHoveredGrid->onMouseOut) {
            unHoveredGrid->onMouseOut();
        }
            
        if(cursorGrid && cursorGrid->onMouseOver) {
            cursorGrid->onMouseOver();
        }
            
        setHoverId(currentId);
    } 
}

void App::onLMouseDown(int x, int y) {
    Grid* cursorGrid = getMouseOver(x, y);

    if(!cursorGrid) return;

    setMouseDownId(cursorGrid->getId());
}

void App::onLMouseUp(int x, int y) {
    Grid* cursorGrid = getMouseOver(x, y);

    if(!cursorGrid) return;

    if(getMouseDownId() == cursorGrid->getId()) {
        if(cursorGrid->onClick)
            cursorGrid->onClick();
    }
}

/// @brief Below are just boilerplate.



void App::onMMouseDown(int x, int y) {

}

void App::onMMouseUp(int x, int y) {

}

void App::onRMouseDown(int x, int y) {

}

void App::onRMouseUp(int x, int y) {

}