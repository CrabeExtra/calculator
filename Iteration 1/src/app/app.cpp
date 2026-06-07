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

    rootGrids.push_back(display.buildCalculatorLayout()); // build the layout of the calculator (will draw this later during render loop)

    window.messageLoop(); // accept input, translate input, handles any changes after showing the window.
};

void App::render() {
    // this will be called during the render loop, and will be responsible for drawing the current page layout to the screen. 
    window.beginDraw();

    try {
        if(rootGrids.empty()) {
            Log::warning("No root grids to render.");
            return;
        }
        display.drawGrid(*rootGrids[activeGrid], window);
    } catch(const std::exception& e) {
        std::string msg = std::string("Exception: ") + e.what();
        Log::error(msg);
    }
    
    window.endDraw();

}

void App::onResize(float width, float height) {
    // do something
    //Log::info("Screen resized. New size: [" + std::to_string(width) + ", " + std::to_string(height) + "]");
    // this will cause an error as is, I don't want to resize anyway for now.
    // rootGrids[0].setWidth(std::to_string(width));
    // rootGrids[0].setHeight(std::to_string(height));
}