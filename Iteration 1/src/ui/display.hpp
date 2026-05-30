#pragma once

#include <string>

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