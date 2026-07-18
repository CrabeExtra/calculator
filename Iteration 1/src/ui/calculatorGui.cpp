#include "display.hpp"
#include "log.hpp"

void Display::buildCalculatorGui(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map) {
    buildCalculatorScreen(rootGrid, map);
    buildCalculatorButtons(rootGrid, map);
}

void onHoverButton(Grid* self) {
    // do something here. Then set on all the buttons.
    // calculator moves upwards 2px, background changes.
}

/**
 * This inverts 
 */
void onMouseOut(Grid* self) {
    // inverse of onHover
}

void onClickButton(Grid* self) {

}



void Display:: buildCalculatorScreen(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map) {
    // Create the grid component.
    Grid* displayRow = new Grid({
        .id = "displayRow",
        .size = { .width = "100%", .height = "110px" },
        .container = rootGrid,
    });

    // Place it in the map
    map.emplace(displayRow->getId(), displayRow);

    Grid* displayRowLeftSpacing = new Grid({
        .id = "displayRowLeftSpacing",
        .size = { .width = "25%", .height = "100%" },
        .container = displayRow,
    });

    map.emplace(displayRowLeftSpacing->getId(), displayRowLeftSpacing);

    Grid* displayColumn = new Grid({
        .id = "displayColumn",
        .size = { .width = "50%", .height = "100%" },
        .style = {
            .gridDirection = GridDirection::Col,
        },
        .container = displayRow
    });

    map.emplace(displayColumn->getId(), displayColumn);

    Grid* displayTopMargin = new Grid({
        .id = "displayTopMargin",
        .size = { .width = "100%", .height = "33.33%" },
        .container = displayColumn
    });

    map.emplace(displayTopMargin->getId(), displayTopMargin);

    Grid* display = new Grid({
        .id = "display",
        .size = { .width = "100%", .height = "33.33%" },
        .style = {
            .text = "0",
        },
        .container = displayColumn
    });

    map.emplace(display->getId(), display);
    
}

void Display::buildCalculatorButtons(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map) {
    auto height = rootGrid->getHeightPx() - 110; // subtract the height of the display.
    auto buttonSpacing = 20.0f;
    auto buttonWidth = (rootGrid->getWidthPx() - (5 * buttonSpacing)) / 4; // 5 buttons per row.
    auto buttonHeight = (height - (6 * buttonSpacing)) / 5; // 4 buttons per column
    
    Grid* buttonsContainer = new Grid( {
        .id = "buttonsContainer",
        .size = { .width = "100%", .height = std::to_string(height) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
        },
        .container = rootGrid,
    });

    map.emplace(buttonsContainer->getId(), buttonsContainer);

    Grid* buttonRow1 = new Grid({
        .id = "buttonRow1",
        .coordinates = { 0.0f, buttonSpacing },
        .size = { .width = "100%", .height = std::to_string(buttonHeight) + "px" },
        .container = buttonsContainer
    });

    map.emplace(buttonRow1->getId(), buttonRow1);

    Grid* modulo = new Grid({
        .id = "modulo",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "%",
        },
        .container = buttonRow1
    });

    map.emplace(modulo->getId(), modulo);

    Grid* clear = new Grid({
        .id = "clear",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "C",
        },
        .container = buttonRow1
    });

    map.emplace(clear->getId(), clear);

    Grid* del = new Grid({
        .id = "del",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "DEL",
        },
        .container = buttonRow1
    });

    map.emplace(del->getId(), del);

    Grid* divide = new Grid({
        .id = "divide",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "÷",
        },
        .container = buttonRow1
    });

    map.emplace(divide->getId(), divide);

    Grid* buttonRow2 = new Grid({
        .id = "buttonRow2",
        .coordinates = { 0.0f, buttonSpacing },
        .size = { .width = "100%", .height = std::to_string(buttonHeight) + "px" },
        .container = buttonsContainer
    });

    map.emplace(buttonRow2->getId(), buttonRow2);

    Grid* seven = new Grid({
        .id = "seven",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "7",
        },
        .container = buttonRow2
    });

    map.emplace(seven->getId(), seven);

    Grid* eight = new Grid({
        .id = "eight",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "8",
        },
        .container = buttonRow2
    });

    map.emplace(eight->getId(), eight);

    Grid* nine = new Grid({
        .id = "nine",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "9",
        },
        .container = buttonRow2
    });

    map.emplace(nine->getId(), nine);

    Grid* multiply = new Grid({
        .id = "multiply",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "x",
        },
        .container = buttonRow2
    });

    map.emplace(multiply->getId(), multiply);

    Grid* buttonRow3 = new Grid({
        .id = "buttonRow3",
        .coordinates = { 0.0f, buttonSpacing },
        .size = { .width = "100%", .height = std::to_string(buttonHeight) + "px" },
        .container = buttonsContainer
    });

    map.emplace(buttonRow3->getId(), buttonRow3);

    Grid* four = new Grid({
        .id = "four",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "4",
        },
        .container = buttonRow3
    });

    map.emplace(four->getId(), four);

    Grid* five = new Grid({
        .id = "five",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "5",
        },
        .container = buttonRow3
    });

    map.emplace(five->getId(), five);

    Grid* six = new Grid({
        .id = "six",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "6",
        },
        .container = buttonRow3
    });

    map.emplace(six->getId(), six);

    Grid* minus = new Grid({
        .id = "minus",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "-",
        },
        .container = buttonRow3
    });

    map.emplace(minus->getId(), minus);

    Grid* buttonRow4 = new Grid({
        .id = "buttonRow4",
        .coordinates = { 0.0f, buttonSpacing },
        .size = { .width = "100%", .height = std::to_string(buttonHeight) + "px" },
        .container = buttonsContainer
    });

    map.emplace(buttonRow4->getId(), buttonRow4);

    Grid* one = new Grid({
        .id = "one",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "1",
        },
        .container = buttonRow4
    });

    map.emplace(one->getId(), one);

    Grid* two = new Grid({
        .id = "two",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "2",
        },
        .container = buttonRow4
    });

    map.emplace(two->getId(), two);

    Grid* three = new Grid({
        .id = "three",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "3",
        },
        .container = buttonRow4
    });

    map.emplace(three->getId(), three);

    Grid* plus = new Grid({
        .id = "plus",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .border_color = 0xFFFFFF,
            .text = "+",
        },
        .container = buttonRow4
    });

    map.emplace(plus->getId(), plus);

    Grid* buttonRow5 = new Grid({
        .id = "buttonRow5",
        .coordinates = { 0.0f, buttonSpacing },
        .size = { .width = "100%", .height = std::to_string(buttonHeight) + "px" },
        .container = buttonsContainer
    });

    map.emplace(buttonRow5->getId(), buttonRow5);

    Grid* spacer = new Grid({
        .id = "spacer",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .container = buttonRow5
    });

    map.emplace(spacer->getId(), spacer);

    Grid* zero = new Grid({
        .id = "zero",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .container = buttonRow5
    });

    map.emplace(zero->getId(), zero);

    Grid* point = new Grid({
        .id = "point",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .container = buttonRow5
    });

    map.emplace(point->getId(), point);

    Grid* equals = new Grid({
        .id = "equals",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .container = buttonRow5
    });

    map.emplace(equals->getId(), equals);
    
}