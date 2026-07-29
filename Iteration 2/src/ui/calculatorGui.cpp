#include "ui.hpp"
#include "log.hpp"

void UI::buildCalculatorGui(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Display& display, Calculator calc) {
    buildCalculatorScreen(rootGrid, map, display);
    buildCalculatorButtons(rootGrid, map, display, calc);
}

void onHoverButton(Grid* self, Display& display) {
    if(!self) {
        Log::warning("Onhover called with null self.");
        return;
    }
    // do something here. Then set on all the buttons.
    // calculator moves upwards 2px, background changes.
    auto& coords = self->getAbsoluteCoords();

    // blot out current spot:
    display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, self->getContainer()->getBackgroundColor(), std::nullopt);

    for(int i = 1; i < coords.size(); i=i+2) {
        coords[i] -= 2;
    }
}

/**
 * This inverts 
 */
void onMouseOut(Grid* self, Display& display) {
    if(!self) {
        Log::warning("OnMouseOut called with null self.");
        return;
    }

    auto& coords = self->getAbsoluteCoords();

    // blot out current spot:
    display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, self->getContainer()->getBackgroundColor(), std::nullopt);

    // inverse of onHover
    for(int i = 1; i < coords.size(); i = i+2) {
        coords[i] += 2;
    }
}

void onClick(std::string op, std::unordered_map<std::string, Grid *>& map, Calculator calc) {
    auto& displayText = map.at("display")->getText(); // could catch this error but there hopefully isn't a case where the calculator display doesn't exist.
    calc.handleInput(op, displayText);
}

void UI:: buildCalculatorScreen(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Display& display) {
    
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
        .style = {
            .gridDirection = GridDirection::Col
        },
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

    Grid* calcDisplay = new Grid({
        .id = "display",
        .size = { .width = "100%", .height = "33.33%" },
        .style = {
            .text = "0",
        },
        .container = displayColumn
    });

    map.emplace(calcDisplay->getId(), calcDisplay);
    
}

void UI::buildCalculatorButtons(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Display& display, Calculator calc) {
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
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "%",
        },
        .container = buttonRow1
    });

    // there has GOT to be a more efficient way to do this.. maybe something that marks something as a button and automatically iterates through and sets the onMouseOver field.
    modulo->setInteractable(true);
    modulo->setOnMouseOver([modulo, &display, this]() {
        display.beginDraw();
        onHoverButton(modulo, display);
        display.drawGrid(*modulo);
        display.endDraw();
    });

    modulo->setOnMouseOut([modulo, &display, this]() {
        display.beginDraw();
        onMouseOut(modulo, display);
        display.drawGrid(*modulo);
        display.endDraw();
    });

    modulo->setOnClick([modulo, &map, calc, &display, this]() {
        onClick(modulo->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(modulo->getId(), modulo);

    Grid* clear = new Grid({
        .id = "clear",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "C",
        },
        .container = buttonRow1
    });

    clear->setInteractable(true);
    clear->setOnMouseOver([clear, &display, this]() {
        display.beginDraw();
        onHoverButton(clear, display);
        display.drawGrid(*clear);
        display.endDraw();
    });

    clear->setOnMouseOut([clear, &display, this]() {
        display.beginDraw();
        onMouseOut(clear, display);
        display.drawGrid(*clear);
        display.endDraw();
    });

    clear->setOnClick([clear, &map, calc, &display, this]() {
        onClick(clear->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(clear->getId(), clear);

    Grid* del = new Grid({
        .id = "del",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "DEL",
        },
        .container = buttonRow1
    });

    del->setInteractable(true);
    del->setOnMouseOver([del, &display, this]() {
        display.beginDraw();
        onHoverButton(del, display);
        display.drawGrid(*del);
        display.endDraw();
    });

    del->setOnMouseOut([del, &display, this]() {
        display.beginDraw();
        onMouseOut(del, display);
        display.drawGrid(*del);
        display.endDraw();
    });

    del->setOnClick([del, &map, calc, &display, this]() {
        onClick(del->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(del->getId(), del);

    Grid* divide = new Grid({
        .id = "divide",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "÷",
        },
        .container = buttonRow1
    });

    divide->setInteractable(true);
    divide->setOnMouseOver([divide, &display, this]() {
        display.beginDraw();
        onHoverButton(divide, display);
        display.drawGrid(*divide);
        display.endDraw();
    });

    divide->setOnMouseOut([divide, &display, this]() {
        display.beginDraw();
        onMouseOut(divide, display);
        display.drawGrid(*divide);
        display.endDraw();
    });

    divide->setOnClick([divide, &map, calc, &display, this]() {
        onClick(divide->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
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
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "7",
        },
        .container = buttonRow2
    });

    seven->setInteractable(true);
    seven->setOnMouseOver([seven, &display, this]() {
        display.beginDraw();
        onHoverButton(seven, display);
        display.drawGrid(*seven);
        display.endDraw();
    });

    seven->setOnMouseOut([seven, &display, this]() {
        display.beginDraw();
        onMouseOut(seven, display);
        display.drawGrid(*seven);
        display.endDraw();
    });

    seven->setOnClick([seven, &map, calc, &display, this]() {
        onClick(seven->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(seven->getId(), seven);

    Grid* eight = new Grid({
        .id = "eight",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "8",
        },
        .container = buttonRow2
    });

    eight->setInteractable(true);
    eight->setOnMouseOver([eight, &display, this]() {
        display.beginDraw();
        onHoverButton(eight, display);
        display.drawGrid(*eight);
        display.endDraw();
    });

    eight->setOnMouseOut([eight, &display, this]() {
        display.beginDraw();
        onMouseOut(eight, display);
        display.drawGrid(*eight);
        display.endDraw();
    });

    eight->setOnClick([eight, &map, calc, &display, this]() {
        onClick(eight->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(eight->getId(), eight);

    Grid* nine = new Grid({
        .id = "nine",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "9",
        },
        .container = buttonRow2
    });

    nine->setInteractable(true);
    nine->setOnMouseOver([nine, &display, this]() {
        display.beginDraw();
        onHoverButton(nine, display);
        display.drawGrid(*nine);
        display.endDraw();
    });

    nine->setOnMouseOut([nine, &display, this]() {
        display.beginDraw();
        onMouseOut(nine, display);
        display.drawGrid(*nine);
        display.endDraw();
    });

    nine->setOnClick([nine, &map, calc, &display, this]() {
        onClick(nine->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(nine->getId(), nine);

    Grid* multiply = new Grid({
        .id = "multiply",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "x",
        },
        .container = buttonRow2
    });

    multiply->setInteractable(true);
    multiply->setOnMouseOver([multiply, &display, this]() {
        display.beginDraw();
        onHoverButton(multiply, display);
        display.drawGrid(*multiply);
        display.endDraw();
    });

    multiply->setOnMouseOut([multiply, &display, this]() {
        display.beginDraw();
        onMouseOut(multiply, display);
        display.drawGrid(*multiply);
        display.endDraw();
    });

    multiply->setOnClick([multiply, &map, calc, &display, this]() {
        onClick(multiply->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
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
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "4",
        },
        .container = buttonRow3
    });

    four->setInteractable(true);
    four->setOnMouseOver([four, &display, this]() {
        display.beginDraw();
        onHoverButton(four, display);
        display.drawGrid(*four);
        display.endDraw();
    });

    four->setOnMouseOut([four, &display, this]() {
        display.beginDraw();
        onMouseOut(four, display);
        display.drawGrid(*four);
        display.endDraw();
    });

    four->setOnClick([four, &map, calc, &display, this]() {
        onClick(four->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(four->getId(), four);

    Grid* five = new Grid({
        .id = "five",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "5",
        },
        .container = buttonRow3
    });

    five->setInteractable(true);
    five->setOnMouseOver([five, &display, this]() {
        display.beginDraw();
        onHoverButton(five, display);
        display.drawGrid(*five);
        display.endDraw();
    });

    five->setOnMouseOut([five, &display, this]() {
        display.beginDraw();
        onMouseOut(five, display);
        display.drawGrid(*five);
        display.endDraw();
    });

    five->setOnClick([five, &map, calc, &display, this]() {
        onClick(five->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(five->getId(), five);

    Grid* six = new Grid({
        .id = "six",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "6",
        },
        .container = buttonRow3
    });

    six->setInteractable(true);
    six->setOnMouseOver([six, &display, this]() {
        display.beginDraw();
        onHoverButton(six, display);
        display.drawGrid(*six);
        display.endDraw();
    });

    six->setOnMouseOut([six, &display, this]() {
        display.beginDraw();
        onMouseOut(six, display);
        display.drawGrid(*six);
        display.endDraw();
    });

    six->setOnClick([six, &map, calc, &display, this]() {
        onClick(six->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(six->getId(), six);

    Grid* minus = new Grid({
        .id = "minus",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "-",
        },
        .container = buttonRow3
    });

    minus->setInteractable(true);
    minus->setOnMouseOver([minus, &display, this]() {
        display.beginDraw();
        onHoverButton(minus, display);
        display.drawGrid(*minus);
        display.endDraw();
    });

    minus->setOnMouseOut([minus, &display, this]() {
        display.beginDraw();
        onMouseOut(minus, display);
        display.drawGrid(*minus);
        display.endDraw();
    });

    minus->setOnClick([minus, &map, calc, &display, this]() {
        onClick(minus->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
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
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "1",
        },
        .container = buttonRow4
    });

    one->setInteractable(true);
    one->setOnMouseOver([one, &display, this]() {
        display.beginDraw();
        onHoverButton(one, display);
        display.drawGrid(*one);
        display.endDraw();
    });

    one->setOnMouseOut([one, &display, this]() {
        display.beginDraw();
        onMouseOut(one, display);
        display.drawGrid(*one);
        display.endDraw();
    });

    one->setOnClick([one, &map, calc, &display, this]() {
        onClick(one->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(one->getId(), one);

    Grid* two = new Grid({
        .id = "two",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "2",
        },
        .container = buttonRow4
    });

    two->setInteractable(true);
    two->setOnMouseOver([two, &display, this]() {
        display.beginDraw();
        onHoverButton(two, display);
        display.drawGrid(*two);
        display.endDraw();
    });

    two->setOnMouseOut([two, &display, this]() {
        display.beginDraw();
        onMouseOut(two, display);
        display.drawGrid(*two);
        display.endDraw();
    });

    two->setOnClick([two, &map, calc, &display, this]() {
        onClick(two->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(two->getId(), two);

    Grid* three = new Grid({
        .id = "three",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "3",
        },
        .container = buttonRow4
    });

    three->setInteractable(true);
    three->setOnMouseOver([three, &display, this]() {
        display.beginDraw();
        onHoverButton(three, display);
        display.drawGrid(*three);
        display.endDraw();
    });

    three->setOnMouseOut([three, &display, this]() {
        display.beginDraw();
        onMouseOut(three, display);
        display.drawGrid(*three);
        display.endDraw();
    });

    three->setOnClick([three, &map, calc, &display, this]() {
        onClick(three->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(three->getId(), three);

    Grid* plus = new Grid({
        .id = "plus",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "+",
        },
        .container = buttonRow4
    });

    plus->setInteractable(true);
    plus->setOnMouseOver([plus, &display, this]() {
        display.beginDraw();
        onHoverButton(plus, display);
        display.drawGrid(*plus);
        display.endDraw();
    });

    plus->setOnMouseOut([plus, &display, this]() {
        display.beginDraw();
        onMouseOut(plus, display);
        display.drawGrid(*plus);
        display.endDraw();
    });

    plus->setOnClick([plus, &map, calc, &display, this]() {
        onClick(plus->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
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
        .style = {
            .gridDirection = GridDirection::Col
        },
        .container = buttonRow5
    });

    map.emplace(spacer->getId(), spacer);

    Grid* zero = new Grid({
        .id = "zero",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "0",
        },
        .container = buttonRow5
    });

    zero->setInteractable(true);
    zero->setOnMouseOver([zero, &display, this]() {
        display.beginDraw();
        onHoverButton(zero, display);
        display.drawGrid(*zero);
        display.endDraw();
    });

    zero->setOnMouseOut([zero, &display, this]() {
        display.beginDraw();
        onMouseOut(zero, display);
        display.drawGrid(*zero);
        display.endDraw();
    });

    zero->setOnClick([zero, &map, calc, &display, this]() {
        onClick(zero->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(zero->getId(), zero);

    Grid* point = new Grid({
        .id = "point",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = ".",
        },
        .container = buttonRow5
    });

    point->setInteractable(true);
    point->setOnMouseOver([point, &display, this]() {
        display.beginDraw();
        onHoverButton(point, display);
        display.drawGrid(*point);
        display.endDraw();
    });

    point->setOnMouseOut([point, &display, this]() {
        display.beginDraw();
        onMouseOut(point, display);
        display.drawGrid(*point);
        display.endDraw();
    });

    point->setOnClick([point, &map, calc, &display, this]() {
        onClick(point->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(point->getId(), point);

    Grid* equals = new Grid({
        .id = "equals",
        .coordinates = { buttonSpacing, 0.0f },
        .size = { .width = std::to_string(buttonWidth) + "px", .height = std::to_string(buttonHeight) + "px" },
        .style = {
            .gridDirection = GridDirection::Col,
            .border_color = 0xFFFFFF,
            .text = "=",
        },
        .container = buttonRow5
    });

    equals->setInteractable(true);
    equals->setOnMouseOver([equals, &display, this]() {
        display.beginDraw();
        onHoverButton(equals, display);
        display.drawGrid(*equals);
        display.endDraw();
    });

    equals->setOnMouseOut([equals, &display, this]() {
        display.beginDraw();
        onMouseOut(equals, display);
        display.drawGrid(*equals);
        display.endDraw();
    });

    equals->setOnClick([equals, &map, calc, &display, this]() {
        onClick(equals->getText(), map, calc);
        display.beginDraw();
        auto& calcDisplay = map.at("display");
        auto& coords = calcDisplay->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        display.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, calcDisplay->getContainer()->getBackgroundColor(), std::nullopt);
        display.drawGrid(*map.at("display"));
        display.endDraw();
    });

    map.emplace(equals->getId(), equals);
    
}