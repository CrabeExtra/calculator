#pragma once

enum class InputAction
{
    None,
    Digit0, Digit1, Digit2, Digit3, Digit4,
    Digit5, Digit6, Digit7, Digit8, Digit9,
    Add, Subtract, Multiply, Divide,
    Equals,
    Clear
};

class InputHandler {
    public:
    InputAction handleKey(int vkCode);
    InputAction handleMouse(int x, int y);
};