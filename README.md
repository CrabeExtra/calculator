# Calculator

This project is essentially building a calculator. This in and of itself is a 5 second task on a WebGUI. 
But this will be far more efficient. I understand I am reinventing the wheel in some senses such as with UI. 
I intend to use this as a learning project. I will become more fluent in C++, more comfortable writing 
applications directly using the Windows API, and more familiar with WinUI, Win32 and other tools native to Windows.

An alterior intention of this task is to build up more reusable code for me to be able to more quickly build
other Windows native programs in.

To build:

cd "./iteration #/build"
cmake ..
cmake --build .

To run: 

1. Find the Debug directory
2. double click on the Calculator.exe

TODO:
- iteration 1
    - linux support, unsure when I'll get to this, but I'm writing it so that it's kind of able to be ported.
    - Generic layout/grid system. Generic buttons etc. Button push tactility etc.
- later iterations
    - More complex calculator calculations, support for larger numbers, overflow handling, more complex numberical methods, brackets, orders etc.
    - add widget support, shortcuts and start menu access.
    - I want to make rendering just once per requirement rather than each loop.
        - I should add absolute locations to each grid object, that way I can have a generic re-render function that just re-renders the part of the page that needs re-rendering.
    