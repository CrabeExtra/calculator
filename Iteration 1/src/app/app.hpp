#pragma once

#include "ui/display.hpp"
#include "layout/grid.hpp"

class App {
    public: 
        App() = default;
        void run(HINSTANCE hInstance, int nCmdShow);
        void render();

    private: 
        int activeGrid = 0;
        Display display;
        std::vector<Grid> rootGrids; // root grids vector, each root grid is essentially a page layout.
};