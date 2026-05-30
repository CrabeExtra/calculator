#pragma once

#include "Windows.h"
#include "../../ui/display.hpp"

class Window {
    static constexpr int WINDOW_WIDTH = 360;
    static constexpr int WINDOW_HEIGHT = 480;
    static constexpr int X = CW_USEDEFAULT;
    static constexpr int Y = CW_USEDEFAULT;

    public: 
        Window(HINSTANCE hInstance, int nCmdShow);
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        LRESULT handleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
        void createWindow();
        void showWindow();
        void messageLoop();

    private:
        HWND hwnd = nullptr;
        HINSTANCE hInstance = nullptr;
        int nCmdShow;
        Display display;
};