#pragma once

#include <string>
#include <optional>
#include <vector>
#include <d2d1.h>
#include <d2d1helper.h>

#include "Windows.h"
#include "../ui/display.hpp"

/**
 * Generic Window class. This is kept OS and rendering API agnostic. Just contains interface required for the grid system. These functions
 * can be implemented per OS and used to create the same APP.
 */
class Window {
    static constexpr int WINDOW_WIDTH = 360;
    static constexpr int WINDOW_HEIGHT = 480;
    static constexpr int X = CW_USEDEFAULT;
    static constexpr int Y = CW_USEDEFAULT;

    public: 
        // core window initialisationa and loop. (might need to revisit these types when making OS agnostic - specifically when looking into Linux implementation)
        Window(HINSTANCE hInstance, int nCmdShow);
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        LRESULT handleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
        void createWindow();
        void showWindow();
        void messageLoop();
        // drawing functions
        uint32_t getColourInt();
        void rectangle(float left, float top, float right, float bottom, std::optional<uint32_t> background_color, std::optional<uint32_t> border_color);
        void roundedRectangle(float left, float top, float right, float bottom, float radiusX, float radiusY, std::optional<uint32_t> background_color, std::optional<uint32_t> border_color);
        void ellipse(float centerX, float centerY, float radiusX, float radiusY, std::optional<uint32_t> background_color, std::optional<uint32_t> border_color);


    private:
        // This helps keep Windows/DirectX specific variables only visible to the win32 implementation
        // and any future Linux implementation only visible to the liux implementation. 
        struct Impl;
        Impl* impl;
};