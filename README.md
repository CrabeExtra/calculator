# Calculator

This project is essentially building a calculator. This in and of itself is a 5 second task on a WebGUI. 
But this will be far more efficient. I understand I am reinventing the wheel in some senses such as with UI. 
I intend to use this as a learning project. I will become more fluent in C++, more comfortable writing 
applications directly using the Windows API, and more familiar with WinUI, Win32 and other tools native to Windows.

An alterior intention of this task is to build up more reusable code for me to be able to more quickly build
other Windows native programs in.

To build (honestly this is mostly just so when I don't use cmake for a while I don't immediately have to relearn it, but with the added benefit of giving noobs the opportunity to run this code):
cd "./Iteration #" 
cmake -S . -B build 
cd "./build"
cmake ..
cmake --build .

Install (at iteration dir):

cd ..
cmake -S . -B build "-DCMAKE_INSTALL_PREFIX=./program"
cmake --build build --config Release
cmake --install build --config Release

-S just specifies the source, -B specifies the build output folder.
.. copies the cmakelists configs and stuff.
--build . compiles and builds (obviously run from the build directory).
To run: 

1. After running the build -> Find the Debug directory
2. double click on the Calculator.exe

Known issues: 
- Don't calculate with an operators the final symbol, I don't have an error guard here, it'll just crash.
    For example calculating '5+' will error. Pretty easy to repair, but not a big issue for a prototype. 
- Currently I've hacked the display to just error if the width of the characters exceeds the width of the screen. This method introduces an error as the % symbol is double the width, resulting in the user being able to cause some overflowed symbols to be burnt into the spacer row below the display. Really I should just truncate the display itself rather than the entire variable. This would also solve the 2 decimal place issue which caps accuracy as well as the display issue.

TODO:
- iteration 1
    - Generic layout/grid system. Generic buttons etc. Button push tactility etc. (Done)
    - completed calculator. (Done)
- Iteration 2
    - I need to completely separate the grid and generic GUI engine from the calculator so I can copy it into its own repository.
    - I should abstract Window away from App. Instead, App should simply have something like a Display object. Which owns window and only exposes necessary functions like render.
    - I also need an input handler that handles all the direct inputs and delegates them to distinct functions. OnHover should be App level as defined on the grid element level, but onMouseMove should be engine level. The following are what need to be moved and where to:
        -   Engine level:
            - drawGrid.
            - onMouseMove (from App, incl. mouseMoveId, hoverId).
            - Construction of Window.
        -   App level:
            - display needs to be renamed to ui and can be made static.
- later iterations
    - linux support, unsure when I'll get to this, but I'm writing it so that it's kind of able to be ported.
    - More complex calculator calculations, support for larger numbers, overflow handling, more complex numberical methods, brackets, orders etc.
    - Add widget support, shortcuts and start menu access.
    - I want to make rendering just once per requirement rather than each loop.
        - I should add absolute locations to each grid object, that way I can have a generic re-render function that just re-renders the part of the page that needs re-rendering.
    - on-hover seems like an expensive operation. Check this later.
        - Note: I've stored each grid in a map. All I need to do is re-render the hovered component.
        - Calculating onhover is just a matter of checking the absolute positions of each grid and comparing with mouse location.
        - I still have to search every single component to compare mouse positions. There has got to be a faster way of implementing this.
        - I read online that a good way to search for components hovered is by segmenting the screen into cells each of which containes a list of components that intersect that given segment.
        - I still feel like there's a much better way to do this.
        - For now I will simply add an 'interacable field' that bubbles up from the interactable component, marking all containers as interactible so the system knows where to search for the cursor and where not to bother.
            Then I'll just search by elements of each the root grid and recurse on the matching absolute coords in a tree-like search so the efficiency is O(Log(n)) rather than O(n).
    - 'World units'. Iteration one uses Pixels or DIPs. Which make sense for a graphical user interface. It does not make sense if I want to pivot this into a rudimentary game engine.
    - I think I need to separate input handling away from app. App shouldn't include handling that will be generic across many apps.
        - platform is OS specific with high crossover with engine specific and reusable.
        - App, Core and UI are app specific.
        - Layout is engine specific and reusable.
        - Log is also engine specific and reusable.

