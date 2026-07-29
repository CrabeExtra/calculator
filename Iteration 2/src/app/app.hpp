#pragma once

#include "ui.hpp"
#include "grid.hpp"
#include "calculator.hpp"
#include "display.hpp"

class App {
    public: 
        App(HINSTANCE hInstance, int nCmdShow) 
            : display(hInstance, nCmdShow)
        {}
        void run();
        void render();
    private: 
        Display display;
        UI ui;
        Calculator calculator;
        
};