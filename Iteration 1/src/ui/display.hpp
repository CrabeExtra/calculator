#pragma once

#include <string>

/**
 * This is pretty basic to be honest. I'll think of more uses for this later on. At the moment though 
 * it kind of just represents 'what will be visible on the calculator screen'.
 * 
 */
class Display
{
    public:
        void setText(const std::string& text);
        void append(char c);
        void clear();

        const std::string& getText() const;

    private:
        std::string currentText;
};