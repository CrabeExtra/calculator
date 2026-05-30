#include "inputHandler.hpp"
#include <windows.h>

InputAction InputHandler::handleKey(int vkCode)
{
    switch (vkCode)
    {
        case '0': return InputAction::Digit0;
        case '1': return InputAction::Digit1;
        case '2': return InputAction::Digit2;
        case '3': return InputAction::Digit3;
        case '4': return InputAction::Digit4;
        case '5': return InputAction::Digit5;
        case '6': return InputAction::Digit6;
        case '7': return InputAction::Digit7;
        case '8': return InputAction::Digit8;
        case '9': return InputAction::Digit9;

        case VK_ADD: return InputAction::Add;
        case VK_SUBTRACT: return InputAction::Subtract;
        case VK_MULTIPLY: return InputAction::Multiply;
        case VK_DIVIDE: return InputAction::Divide;

        case VK_RETURN: return InputAction::Equals;
        case VK_ESCAPE: return InputAction::Clear;

        default: return InputAction::None;
    }
}