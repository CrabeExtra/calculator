#include <exception>

#include "app.hpp"
#include "window.hpp"
#include "window_impl.hpp"
#include "theme.hpp"
#include "log.hpp"



/**
 * Creates the window, displays the window, begins core loop.
 */
void App::run() {

    window.createWindow(); // create the window (duh)

    window.showWindow(); // show the window (duh)

    display.buildCalculatorLayout(); // build the layout of the calculator (will draw this later during render loop)

    window.messageLoop(); // accept input, translate input, handles any changes after showing the window.
};

void App::render() {
    // this will be called during the render loop, and will be responsible for drawing the current page layout to the screen. 
    window.beginDraw();

    //window.roundedRectangle(0.5f, 0.5f, 100.5f, 100.5f, 10.0f, 10.0f, Theme::ButtonFillPrimary, Theme::ButtonBorderPrimary);
    try {
        Log::info("Rendering grid...");
        //display.drawGrid(rootGrids[activeGrid], window);
    } catch(const std::exception& e) {
        std::string msg = std::string("Exception: ") + e.what();
        Log::error(msg);
    }
    
    window.endDraw();

}