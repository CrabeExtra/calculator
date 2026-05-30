
#include "platform/win32/window.hpp"
#include "app.hpp"
/**
 * Creates the window, displays the window, begins core loop.
 */
void App::run(HINSTANCE hInstance, int nCmdShow) {
    Window window(hInstance, nCmdShow);

    window.createWindow(); // create the window (duh)

    window.showWindow(); // show the window (duh)

    window.messageLoop(); // accept input, translate input. Need to review what this is doing..
};