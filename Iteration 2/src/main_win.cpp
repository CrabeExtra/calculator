#include "Windows.h"

#include "app.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    App app(hInstance, nCmdShow);

    app.run();

    return 0;
}