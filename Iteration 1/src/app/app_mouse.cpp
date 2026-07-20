#include <queue>

#include "app.hpp"
#include "log.hpp"

// if g is not interactable, no need to search. No contained elements are interactable by design.
// if not within the coordinates of the g, then don't bother checking.
bool isValidElement(Grid* element, int x, int y) {

    auto& coords = element->getAbsoluteCoords(); // should make this const at some point to satisfy best practices.
    return element->getInteractable() && (
        x >= coords[0]
        && x <= coords[2]
        && y >= coords[1]
        && y <= coords[3]
    );
}

Grid* App::getMouseOver(int x, int y) {
    // just assuming these already exist. Note on floating "root" text here.
    std::unordered_map<std::string, Grid *>& map = rootGrids[activeGridIndex];
    Grid* g = map["root"]; // TODO: what to do with the floating "root".

    // check validity of the root element. if unnecessary to check, don't begin iterating.
    if(!isValidElement(g, x, y)) {
        return nullptr;
    }

    Grid* currentGrid = g;
    // using recursion would break down for many elements. I know I've used recursion elsewhere in this program though - I should move away from recursion if I plan on reusing the code for more complex projects.
    while(true) {
        std::vector<Grid*> elements = currentGrid->getElements();

        // might change this later to element and ensure hover bubbles up. Not for now.
        bool foundInteractiveLeaf = false;

        // from the last rendered element to the first rendered element (to ensure on-top elemnts within he same container are selected), iterate.
        for(int i = (int)elements.size() - 1; i >= 0; i--) {
            // A key assumption here is that the person writing the ui code knows that elements should be spacially contained within their container, and that elements do not overlap, although I have handled this as mentioned in the comment above.
            if(isValidElement(elements[i], x, y)) {
                currentGrid = elements[i];  // found the valid element, set to current and continue.
                foundInteractiveLeaf = true;        
                break;
            }
        }

        if(!foundInteractiveLeaf) {
            return currentGrid; // current grid was searched and no interactible contained elements. Then this element is the element being clicked.
        }; // exit condition, looped elements and found nothing, this is the leaf node.
        
    }
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