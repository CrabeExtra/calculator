
#include "platform/win32/window.hpp"
#include "app.hpp"

void App::run(HINSTANCE hInstance, int nCmdShow) {
    Window window(hInstance, nCmdShow);

    window.createWindow();

    window.showWindow();

    window.messageLoop();
};