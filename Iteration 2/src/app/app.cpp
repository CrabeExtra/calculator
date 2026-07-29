#include <exception>

#include "app.hpp"
#include "log.hpp"
/**
 * Creates the window, displays the window, begins core loop.
 */
void App::run() {

    display.initWindow();

    ui.buildCalculatorLayout(display.getRootGrids(), display, calculator); // build the layout of the calculator (will draw this later during render loop)

    display.invalidateWindow(); // tell window 'building is finished, trigger a render'

    display.startMessageLoop(); // accept input, translate input, handles any changes after showing the window.
};

