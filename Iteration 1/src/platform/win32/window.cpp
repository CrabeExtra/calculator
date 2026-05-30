#include "window.hpp"

#include "Windows.h"

Window::Window(HINSTANCE _hInstance, int _nCmdShow) {
    hInstance = _hInstance;
    nCmdShow = _nCmdShow;
}

void Window::createWindow() {

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Calculator"; // name of my window.

    WNDCLASSW wc = { }; // this holds all information regarding the window - style, icon, cursor, background

    wc.lpfnWndProc   = WindowProc; // assigns callback function that handles interactions such as clicks or keyboard inputs.
    wc.hInstance     = hInstance; // application instance handle, kind of like setting the process ID. It's how the OS tracks this window.
    wc.lpszClassName = CLASS_NAME; // Assigns the name of the window to the window.

    RegisterClassW(&wc);

    // Create the window.

    hwnd = CreateWindowExW(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Calculator",                  // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        X, // X
        Y, // Y
        WINDOW_WIDTH, // Width
        WINDOW_HEIGHT, // Height
        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return;
    }

    ShowWindow(hwnd, nCmdShow);
}


LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Window::showWindow()
{
    if (!hwnd) return;

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

void Window::messageLoop()
{
    MSG msg = {};

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}