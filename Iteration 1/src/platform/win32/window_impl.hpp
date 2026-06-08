
#include "Windows.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <functional>
#include <wincodec.h>
#include <dwrite.h>

#include "../window.hpp"
#include "app.hpp"


struct Window::Impl {
    HWND hwnd = nullptr;
    HINSTANCE hInstance = nullptr;
    int nCmdShow;
    ID2D1HwndRenderTarget* pRenderTarget = nullptr;
    ID2D1SolidColorBrush* pBrush = nullptr;
    ID2D1Factory* factory = nullptr;
    IDWriteFactory* pDWriteFactory;
    IWICImagingFactory* wicFactory = nullptr;
    std::function<void()> render = nullptr;
    std::function<void(float width, float height)> onResize;
    int height;
    int width;
};

struct Window::Image {
    
};