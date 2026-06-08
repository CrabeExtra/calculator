#include <exception>

#include "app.hpp"
#include "window.hpp"
#include "window_impl.hpp"
#include "log.hpp"

/**
 * Creates the window, displays the window, begins core loop.
 */
void App::run() {

    window.createWindow(); // create the window (duh)

    window.showWindow(); // show the window (duh)
    
    display.buildCalculatorLayout(rootGrids); // build the layout of the calculator (will draw this later during render loop)
    
    window.messageLoop(); // accept input, translate input, handles any changes after showing the window.
};

void App::render() {
    // this will be called during the render loop, and will be responsible for drawing the current page layout to the screen. 
    window.beginDraw();

    try {
        if(rootGrids.empty()) {
            Log::warning("No root grids to render.");
            throw std::exception("Rendering error. See logs.");
        }

        if(!getDrawId().empty()) {

            if(activeGrid >= rootGrids.size()) {
                Log::error("Attempting to access active grid out of bounds.");
                Log::error("Active grid: " + std::to_string(activeGrid));
                Log::error("Maximum active grid: " + rootGrids.size());
                throw std::exception("Rendering error. See logs.");
            }

            auto& map = rootGrids[activeGrid]; // if this errors it will catch anyway.
            auto mapEntry = map.find(getDrawId());

            if(mapEntry == map.end()) {
                Log::error("RootGrids improperly initialised. RootGrid entirely missing during rendering.");
                Log::error("Draw ID: " + getDrawId());
                throw std::exception("Rendering error. See logs.");
            }

            Grid* g = mapEntry->second;

            if(g == nullptr) {
                Log::error("RootGrid null during rendering.");
                Log::error("Draw ID: " + getDrawId());
                throw std::exception("Rendering error. See logs.");
            }
            
            display.drawGrid(*g, window); // draw the grid.

            setDrawId(""); // Once drawn, set the draw ID to empty to prevent unnecessary re-renders.
        }

        
    } catch(const std::exception& e) {
        std::string msg = std::string("Exception: ") + e.what();
        Log::error(msg);
    }
    
    window.endDraw();

}

void App::onResize(float width, float height) {
    setDrawId("root");
    render();
}