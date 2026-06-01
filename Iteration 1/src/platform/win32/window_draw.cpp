#include <d2d1.h>
#include <d2d1helper.h> // apparently it's good standard practice to include imports even though they already exist in the header file.

#include "../window.hpp"
#include "window_impl.hpp"

void Window::rectangle(float left, float top, float right, float bottom, std::optional<uint32_t> background_color, std::optional<uint32_t> border_color) {
    uint32_t originalColour = getColourInt(); 

    D2D1_RECT_F rect = D2D1::RectF(left, top, right, bottom);
    
    if(background_color) {
        impl->pBrush->SetColor(D2D1::ColorF(*background_color));
        impl->pRenderTarget->FillRectangle(rect, impl->pBrush);
    } 

    if(border_color) { 
        impl->pBrush->SetColor(D2D1::ColorF(*border_color));
        impl->pRenderTarget->DrawRectangle(rect, impl->pBrush);
    }

    impl->pBrush->SetColor(D2D1::ColorF(originalColour)); // reset colour - preserves default colour.
}

void Window::roundedRectangle(float left, float top, float right, float bottom, float radiusX, float radiusY, std::optional<uint32_t> background_color, std::optional<uint32_t> border_color) {
        uint32_t originalColour = getColourInt(); 
    
        D2D1_ROUNDED_RECT roundedRect = D2D1::RoundedRect(
            D2D1::RectF(left, top, right, bottom),
            radiusX,
            radiusY
        );
        
        if(background_color) {
            impl->pBrush->SetColor(D2D1::ColorF(*background_color));
            impl->pRenderTarget->FillRoundedRectangle(roundedRect, impl->pBrush);
        } 
    
        if(border_color) { 
            impl->pBrush->SetColor(D2D1::ColorF(*border_color));
            impl->pRenderTarget->DrawRoundedRectangle(roundedRect, impl->pBrush);
        }
    
        impl->pBrush->SetColor(D2D1::ColorF(originalColour)); // reset colour - preserves default colour.
}

void Window::ellipse(float centerX, float centerY, float radiusX, float radiusY, std::optional<uint32_t> background_color, std::optional<uint32_t> border_color) {
    uint32_t originalColour = getColourInt(); 

    D2D1_ELLIPSE ellipse = D2D1::Ellipse(
        D2D1::Point2F(centerX, centerY),
        radiusX,
        radiusY
    );

    if(background_color) {
        impl->pBrush->SetColor(D2D1::ColorF(*background_color));
        impl->pRenderTarget->FillEllipse(ellipse, impl->pBrush);
    }

    if(border_color) {
        impl->pBrush->SetColor(D2D1::ColorF(*border_color));
        impl->pRenderTarget->DrawEllipse(ellipse, impl->pBrush);
    }

    impl->pBrush->SetColor(D2D1::ColorF(originalColour)); // reset colour - preserves default colour.
}

uint32_t Window::getColourInt() {
    D2D1_COLOR_F dxColour = impl->pBrush->GetColor(); 
    return RGB(
        static_cast<uint8_t>(dxColour.r * 255),
        static_cast<uint8_t>(dxColour.g * 255),
        static_cast<uint8_t>(dxColour.b * 255)
    );
}