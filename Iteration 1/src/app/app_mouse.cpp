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

/**
 * Function to check for hits.
 * Re
 */
void App::onMouseMove(int x, int y) {
    
    // just assuming these already exist. Note on floating "root" text here.
    std::unordered_map<std::string, Grid *> map = rootGrids[activeGridIndex];
    Grid* g = map["root"];
    

    // check validity of the root element. if unnecessary to check, don't begin iterating.
    if(!isValidElement(g, x, y)) {
        return;
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
                currentGrid = elements[i];  // found the valid element, set to current and recurse.
                foundInteractiveLeaf = true;        
                break;
            }
        }

        if(!foundInteractiveLeaf) break; // exit condition, looped elements and found nothing, this is the leaf node.
        
    }

    // this will need recreating for the case where wa want to add bubbling up to onhover.

    // mouse has left wherever else it may have been pointing.
    // if(!hoverId.empty()) {
    //     Grid* previouslyHoveredGrid = map[hoverId];

    //     if(previouslyHoveredGrid->onMouseOut)
    //         previouslyHoveredGrid->onMouseOut();
    // }

    // // act on currently hovered.
    
    // hoverId = currentGrid->getId();
    // if(currentGrid->onMouseOver)
    //     currentGrid->onMouseOver();
}