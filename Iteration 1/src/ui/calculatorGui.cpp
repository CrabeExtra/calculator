#include "display.hpp"
#include "log.hpp"

void Display::buildCalculatorGui(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map) {
    buildCalculatorScreen(rootGrid, map);
    buildCalculatorButtons(rootGrid, map);
}

void onHoverButton(Grid* self) {
    // do something here. Then set on all the buttons.
}

void onClickButton(Grid* self) {

}

void onMouseOut(Grid* self) {

}

void Display:: buildCalculatorScreen(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map) {
    Grid* displayRow = new Grid(
        "displayRow",
        "100%",
        "110px",
        std::vector<float> { 0.0f, 0.0f },
        rootGrid,
        std::nullopt,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(displayRow->getId(), displayRow);

    Grid* displayRowLeftSpacing = new Grid(
        "displayRowLeftSpacing",
        "25%",
        "100%",
        std::vector<float> { 0.0f, 0.0f },
        displayRow,
        GridDirection::Col,
        std::nullopt,
        std::nullopt, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(displayRowLeftSpacing->getId(), displayRowLeftSpacing);

    Grid* displayColumn = new Grid(
        "displayColumn",
        "50%",
        "100%",
        std::vector<float> { 0.0f, 0.0f },
        displayRow,
        GridDirection::Col,
        std::nullopt,
        std::nullopt, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(displayColumn->getId(), displayColumn);

    Grid* displayTopMargin = new Grid(
        "displayTopMargin",
        "100%",
        "33.33%",
        std::vector<float> { 0.0f, 0.0f },
        displayColumn,
        GridDirection::Row,
        std::nullopt,
        std::nullopt, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(displayTopMargin->getId(), displayTopMargin);

    Grid* display = new Grid(
        "display",
        "100%",
        "33.33%",
        std::vector<float> { 0.0f, 0.0f },
        displayColumn,
        GridDirection::Row,
        std::nullopt,
        std::nullopt, // border colour
        "0", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(display->getId(), display);
    
}

void Display::buildCalculatorButtons(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map) {
    auto height = rootGrid->getHeightPx() - 110; // subtract the height of the display.
    auto buttonSpacing = 20.0f;
    auto buttonWidth = (rootGrid->getWidthPx() - (5 * buttonSpacing)) / 4; // 5 buttons per row.
    auto buttonHeight = (height - (6 * buttonSpacing)) / 5; // 4 buttons per column
    
    Grid* buttonsContainer = new Grid(
        "buttonsContainer",
        "100%",
        std::to_string(height) + "px",
        std::vector<float> { 0.0f, 0.0f },
        rootGrid,
        std::nullopt,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(buttonsContainer->getId(), buttonsContainer);

    Grid* buttonRow1 = new Grid(
        "buttonRow1",
        "100%",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { 0.0f, buttonSpacing }, // set y axis spacing at the row level.
        buttonsContainer,
        std::nullopt,
        std::nullopt, // background colour
        std::nullopt, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(buttonRow1->getId(), buttonRow1);

    Grid* modulo = new Grid(
        "modulo",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow1,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "%", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(modulo->getId(), modulo);

    Grid* clear = new Grid(
        "clear",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow1,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "C", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(clear->getId(), clear);

    Grid* del = new Grid(
        "del",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow1,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "del", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(del->getId(), del);

    Grid* divide = new Grid(
        "divide",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow1,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "÷", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(divide->getId(), divide);

    Grid* buttonRow2 = new Grid(
        "buttonRow2",
        "100%",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { 0.0f, buttonSpacing }, // set y axis spacing at the row level.
        buttonsContainer,
        std::nullopt,
        std::nullopt, // background colour
        std::nullopt, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(buttonRow2->getId(), buttonRow2);

    Grid* seven = new Grid(
        "seven",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow2,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "7", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(seven->getId(), seven);

    Grid* eight = new Grid(
        "eight",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow2,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "8", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(eight->getId(), eight);

    Grid* nine = new Grid(
        "nine",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow2,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "9", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(nine->getId(), nine);

    Grid* multiply = new Grid(
        "multiply",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow2,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "x", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(multiply->getId(), multiply);

    Grid* buttonRow3 = new Grid(
        "buttonRow3",
        "100%",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { 0.0f, buttonSpacing }, // set y axis spacing at the row level.
        buttonsContainer,
        std::nullopt,
        std::nullopt, // background colour
        std::nullopt, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(buttonRow3->getId(), buttonRow3);

    Grid* four = new Grid(
        "four",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow3,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "4", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(four->getId(), four);

    Grid* five = new Grid(
        "five",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow3,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "5", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(five->getId(), five);

    Grid* six = new Grid(
        "six",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow3,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "6", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(six->getId(), six);

    Grid* minus = new Grid(
        "minus",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow3,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "-", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(minus->getId(), minus);

    Grid* buttonRow4 = new Grid(
        "buttonRow4",
        "100%",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { 0.0f, buttonSpacing }, // set y axis spacing at the row level.
        buttonsContainer,
        std::nullopt,
        std::nullopt, // background colour
        std::nullopt, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(buttonRow4->getId(), buttonRow4);

    Grid* one = new Grid(
        "one",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow4,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "1", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(one->getId(), one);

    Grid* two = new Grid(
        "two",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow4,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "2", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(two->getId(), two);

    Grid* three = new Grid(
        "three",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow4,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "3", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(three->getId(), three);

    Grid* plus = new Grid(
        "plus",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow4,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "+", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(plus->getId(), plus);

    Grid* buttonRow5 = new Grid(
        "buttonRow5",
        "100%",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { 0.0f, buttonSpacing }, // set y axis spacing at the row level.
        buttonsContainer,
        std::nullopt,
        std::nullopt, // background colour
        std::nullopt, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(buttonRow5->getId(), buttonRow5);

    Grid* spacer = new Grid(
        "spacer",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow5,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(spacer->getId(), spacer);

    Grid* zero = new Grid(
        "zero",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow5,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "0", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(zero->getId(), zero);

    Grid* point = new Grid(
        "point",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow5,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        ".", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(point->getId(), point);

    Grid* equals = new Grid(
        "equals",
        std::to_string(buttonWidth) + "px",
        std::to_string(buttonHeight) + "px", 
        std::vector<float> { buttonSpacing, 0.0f }, // set x axis spacing at button level.
        buttonRow5,
        GridDirection::Col,
        std::nullopt, // background colour
        0xFFFFFF, // border colour
        "=", // text
        std::nullopt, // default borderShape (rectangle)
        std::nullopt, // border radius width
        std::nullopt  // border radius height
    );

    map.emplace(equals->getId(), equals);
    
}