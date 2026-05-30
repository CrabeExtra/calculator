#include <windows.h>
#include "display.hpp"

void Display::setText(const std::string& text)
{
    currentText = text;
}

void Display::append(char c)
{
    currentText += c;
}

void Display::clear()
{
    currentText.clear();
}

const std::string& Display::getText() const
{
    return currentText;
}