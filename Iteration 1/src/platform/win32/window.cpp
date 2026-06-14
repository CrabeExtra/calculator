#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include "Windows.h"

#include "../window.hpp"
#include "../theme.hpp"
#include "window_impl.hpp"
#include "app.hpp"

Window::Window(HINSTANCE _hInstance, int _nCmdShow, std::function<void()> render, std::optional<std::function<void(float width, float height)>> onResize) {
    impl = new Impl();
    impl->hInstance = _hInstance;
    impl->nCmdShow = _nCmdShow;
    impl->render = render;
    impl->onResize = *onResize;
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
        NULL,       // Container window    
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

                // INITIALISE WINDOW SIZE
                RECT rc;
                GetClientRect(hwnd, &rc);

                UINT width = rc.right - rc.left;
                UINT height = rc.bottom - rc.top;

                window->impl->height = height;
                window->impl->width = width;

                // DIRECT2D INITIALISATION
                D2D1CreateFactory(
                    D2D1_FACTORY_TYPE_SINGLE_THREADED, // review use cases
                    &window->impl->factory
                );

                D2D1_HWND_RENDER_TARGET_PROPERTIES hwndProps =
                    D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(width, height));

                D2D1_RENDER_TARGET_PROPERTIES rtProps =
                    D2D1::RenderTargetProperties();

                // initialise render target.
                /*HRESULT hr = **/window->impl->factory->CreateHwndRenderTarget(
                    rtProps,
                    hwndProps,
                    &window->impl->pRenderTarget
                );

                window->impl->pRenderTarget->Resize(D2D1::SizeU(width, height));
                InvalidateRect(hwnd, nullptr, TRUE);
                UpdateWindow(hwnd);

                // initialise brush.
                window->impl->pRenderTarget->CreateSolidColorBrush(
                    D2D1::ColorF(0xFFFFFF),
                    &window->impl->pBrush
                );

                // initialise image loader
                CoInitialize(nullptr);  
                window->impl->wicFactory = nullptr;
                
                // initialise writer
                DWriteCreateFactory(
                    DWRITE_FACTORY_TYPE_SHARED,
                    __uuidof(IDWriteFactory),
                    reinterpret_cast<IUnknown**>(&window->impl->pDWriteFactory)
                );

                window->impl->pDWriteFactory->CreateTextFormat(
                    L"Segoe UI",
                    nullptr,
                    DWRITE_FONT_WEIGHT_NORMAL,
                    DWRITE_FONT_STYLE_NORMAL,
                    DWRITE_FONT_STRETCH_NORMAL,
                    24.0f,
                    L"en-us",
                    &window->impl->pTextFormat
                );

                // TODO: handle if hr is error response 

                return TRUE;
            }
        case WM_PAINT:
            {
                Window* window =
                    (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
                
                if(window) {
                    window->impl->render();
                }
                return 0;
            }
        case WM_SIZE:
        {
            // resize render target on window resize. Prevents stretching of components that shouldn't be stretched.
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);

            if(width == 0 || height == 0) return 0; // for some reason it sets my screen to (0,0) initially unless I prevent it.

            Window* window =
                (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

            if (window->impl->pRenderTarget)
            {
                // ensure width and height doesn't stretch (resize the render target to match new window size)
                window->impl->pRenderTarget->Resize(D2D1::SizeU(width, height));

                // refresh window size
                window->impl->height = height;
                window->impl->width = width;
            }

            if(window->impl->onResize) {
                window->impl->onResize((float)width, (float)height);
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

int Window::viewWidth() { return impl->width; }
int Window::viewHeight() { return impl->height; }