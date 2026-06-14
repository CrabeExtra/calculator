#pragma once

#include "display.hpp"
#include "grid.hpp"
#include "window.hpp"

class App {
    public: 
        App(HINSTANCE hInstance, int nCmdShow) : 
            window(
                hInstance, 
                nCmdShow, 
                [this]() { this->render(); }, 
                [this](float width, float height) { this->onResize(width, height); }, 
                [this](int x, int y) { this->onMouseMove(x, y); }
            ), 
            display(), 
            rootGrids() 
        {}
        void run();
        void render();
        void onResize(float width, float height);
        void onMouseMove(int x, int y);

        std::string getDrawId() { return drawId; };
        
        void setDrawId(const std::string& drawId) { this->drawId = drawId; };

    private: 
        int activeGridIndex = 0;
        Window window;
        Display display;
        std::vector<std::unordered_map<std::string, Grid*>> rootGrids; // root grids vector, each root grid is essentially a page layout. I've added unordered map
                                                                       // so that grids can be indexed by ID. Please not that the grid with ID "root" is always the root grid.
        std::string drawId = "root";
        std::string hoverId = "";
};