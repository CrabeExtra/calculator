
#include "Windows.h"
#include <d2d1.h>
#include <d2d1helper.h>

#include "../window.hpp"

struct Window::Impl {
    HWND hwnd = nullptr;
    HINSTANCE hInstance = nullptr;
    int nCmdShow;
    ID2D1HwndRenderTarget* pRenderTarget = nullptr;
    ID2D1SolidColorBrush* pBrush = nullptr;
    ID2D1Factory* factory = nullptr;
};