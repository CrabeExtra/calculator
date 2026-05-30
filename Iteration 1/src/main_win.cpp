#include "Windows.h"

#include "app/app.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    App app;

    app.run(hInstance, nCmdShow);

    return 0;
}