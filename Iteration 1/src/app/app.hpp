#pragma once

#include "display.hpp"
#include "grid.hpp"
#include "window.hpp"
#include "calculator.hpp"

class App {
    public: 
        App(HINSTANCE hInstance, int nCmdShow) : 
            window( // TODO: I'm sure there's a better place/pattern to hardcode these. Suych as an input handler instead of in App.hpp.
                hInstance, 
                nCmdShow, 
                [this]() { this->render(); }, 
                [this](float width, float height) { this->onResize(width, height); }, 
                [this](int x, int y) { this->onMouseMove(x, y); },
                [this](int x, int y) { this->onLMouseDown(x, y); },
                [this](int x, int y) { this->onLMouseUp(x, y); },
                [this](int x, int y) { this->onMMouseDown(x, y); },
                [this](int x, int y) { this->onMMouseUp(x, y); },
                [this](int x, int y) { this->onRMouseDown(x, y); },
                [this](int x, int y) { this->onRMouseUp(x, y); },
                [this](Key k) { this-> onKeyDown(k); },
                [this](Key k) { this-> onKeyUp(k); }
            ), 
            display(), 
            rootGrids() 
        {}
        void run();
        void render();
        void onResize(float width, float height);
        void onMouseMove(int x, int y);
        void onLMouseDown(int x, int y);
        void onLMouseUp(int x, int y);
        void onMMouseDown(int x, int y);
        void onMMouseUp(int x, int y);
        void onRMouseDown(int x, int y);
        void onRMouseUp(int x, int y);
        void onKeyDown(Key k);
        void onKeyUp(Key k);

        void setMouseDownId(std::string id) { mouseDownId = id; };
        void setHoverId(std::string id) { hoverId = id; };

        std::string getMouseDownId() { return mouseDownId; };
        std::string getHoverId() { return hoverId; };
        /// @brief What is the mouse currently hovering.
        /// @param x 
        /// @param y 
        /// @return 
        Grid* getMouseOver(int x, int y);
        
        std::string getDrawId() { return drawId; };
        
        void setDrawId(const std::string& drawId) { this->drawId = drawId; };

    private: 
        int activeGridIndex = 0;
        Window window;
        Display display;
        Calculator calculator;
        std::vector<std::unordered_map<std::string, Grid*>> rootGrids; // root grids vector, each root grid is essentially a page layout. I've added unordered map
                                                                       // so that grids can be indexed by ID. Please not that the grid with ID "root" is always the root grid.
        std::string drawId = "root";
        std::string hoverId = "";
        std::string mouseDownId = "";
};