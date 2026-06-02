#pragma once

#include "display.hpp"
#include "grid.hpp"
#include "window.hpp"

class App {
    public: 
        App(HINSTANCE hInstance, int nCmdShow) : window(hInstance, nCmdShow, [this]() { this->render(); }, [this](float width, float height) { this->onResize(width, height); }), display(), rootGrids() {}
        void run();
        void render();
        void onResize(float width, float height);

    private: 
        int activeGrid = 0;
        Window window;
        Display display;
        std::vector<Grid*> rootGrids; // root grids vector, each root grid is essentially a page layout.
};