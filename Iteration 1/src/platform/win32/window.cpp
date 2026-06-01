#include <string>
#include <vector>
#include <iostream>
#include "Windows.h"

#include "../window.hpp"
#include "../theme.hpp"
#include "window_impl.hpp"

Window::Window(HINSTANCE _hInstance, int _nCmdShow) {
    impl = new Impl();
    impl->hInstance = _hInstance;
    impl->nCmdShow = _nCmdShow;
}

void Window::createWindow() {

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Calculator"; // name of my window.

    WNDCLASSW wc = { }; // this holds all information regarding the window - style, icon, cursor, background

    wc.lpfnWndProc   = WindowProc; // assigns callback function that handles interactions such as clicks or keyboard inputs.
    wc.hInstance     = impl->hInstance; // application instance handle, kind of like setting the process ID. It's how the OS tracks this window.
    wc.lpszClassName = CLASS_NAME; // Assigns the name of the window to the window.

    RegisterClassW(&wc);

    // Create the window.

    impl->hwnd = CreateWindowExW(
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
        impl->hInstance,  // Instance handle
        this        // Additional application data (just injecting window context)
        );

    if (impl->hwnd == NULL)
    {
        return;
    }
}


LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_NCCREATE: 
            {
                // INITIALISE 'THIS' POINTER
                // get 'this' window (this is a static callback so can't directly.)
                CREATESTRUCT* cs = (CREATESTRUCT*)lParam;

                // use 'this' to store this instance of window.
                Window* window = (Window*)cs->lpCreateParams;

                SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);

                // DIRECT2D INITIALISATION
                D2D1CreateFactory(
                    D2D1_FACTORY_TYPE_SINGLE_THREADED, // review use cases
                    &window->impl->factory
                );

                D2D1_HWND_RENDER_TARGET_PROPERTIES hwndProps =
                    D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(WINDOW_WIDTH, WINDOW_HEIGHT));

                D2D1_RENDER_TARGET_PROPERTIES rtProps =
                    D2D1::RenderTargetProperties();

                // initialise render target.
                /*HRESULT hr = **/window->impl->factory->CreateHwndRenderTarget(
                    rtProps,
                    hwndProps,
                    &window->impl->pRenderTarget
                );

                // initialise brush.
                window->impl->pRenderTarget->CreateSolidColorBrush(
                    D2D1::ColorF(0xFFFFFF),
                    &window->impl->pBrush
                );

                // TODO: handle if hr is error response 

                return TRUE;
            }
        case WM_PAINT:
            {
                Window* window =
                    (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

                if(window) {
                    // TODO: move beginDraw and EndDraw to another function that renders the page.
                    window->impl->pRenderTarget->BeginDraw();

                    window->roundedRectangle(0.5f, 0.5f, 100.5f, 100.5f, 10.0f, 10.0f, Theme::ButtonFillPrimary, Theme::ButtonBorderPrimary);

                    window->impl->pRenderTarget->EndDraw();
                }
            }
        case WM_SIZE:
        {
            // resize render target on window resize. Prevents stretching of components that shouldn't be stretched.
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            Window* window =
                (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

            if (window->impl->pRenderTarget)
            {
                window->impl->pRenderTarget->Resize(D2D1::SizeU(width, height));
            }
            return 0;
        }
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Window::showWindow()
{
    if (!impl->hwnd) return;

    ShowWindow(impl->hwnd, SW_SHOW);
    UpdateWindow(impl->hwnd);
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