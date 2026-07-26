#include "display.hpp"
#include "log.hpp"

void Display::buildCalculatorGui(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Window& window, Calculator calc) {
    buildCalculatorScreen(rootGrid, map, window);
    buildCalculatorButtons(rootGrid, map, window, calc);
}

void onHoverButton(Grid* self, Window& window) {
    if(!self) {
        Log::warning("Onhover called with null self.");
        return;
    }
    // do something here. Then set on all the buttons.
    // calculator moves upwards 2px, background changes.
    auto& coords = self->getAbsoluteCoords();

    // blot out current spot:
    window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, self->getContainer()->getBackgroundColor(), std::nullopt);

    for(int i = 1; i < coords.size(); i=i+2) {
        coords[i] -= 2;
    }
}

/**
 * This inverts 
 */
void onMouseOut(Grid* self, Window& window) {
    if(!self) {
        Log::warning("OnMouseOut called with null self.");
        return;
    }

    auto& coords = self->getAbsoluteCoords();

    // blot out current spot:
    window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, self->getContainer()->getBackgroundColor(), std::nullopt);

    // inverse of onHover
    for(int i = 1; i < coords.size(); i = i+2) {
        coords[i] += 2;
    }
}

void onClick(std::string op, std::unordered_map<std::string, Grid *>& map, Calculator calc) {
    auto& displayText = map.at("display")->getText(); // could catch this error but there hopefully isn't a case where the calculator display doesn't exist.
    calc.handleInput(op, displayText);
}

void Display:: buildCalculatorScreen(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Window& window) {
    
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

void Display::buildCalculatorButtons(Grid* rootGrid, std::unordered_map<std::string, Grid *>& map, Window& window, Calculator calc) {
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
    modulo->setOnMouseOver([modulo, &window, this]() {
        window.beginDraw();
        onHoverButton(modulo, window);
        drawGrid(*modulo, window);
        window.endDraw();
    });

    modulo->setOnMouseOut([modulo, &window, this]() {
        window.beginDraw();
        onMouseOut(modulo, window);
        drawGrid(*modulo, window);
        window.endDraw();
    });

    modulo->setOnClick([modulo, &map, calc, &window, this]() {
        onClick(modulo->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    clear->setOnMouseOver([clear, &window, this]() {
        window.beginDraw();
        onHoverButton(clear, window);
        drawGrid(*clear, window);
        window.endDraw();
    });

    clear->setOnMouseOut([clear, &window, this]() {
        window.beginDraw();
        onMouseOut(clear, window);
        drawGrid(*clear, window);
        window.endDraw();
    });

    clear->setOnClick([clear, &map, calc, &window, this]() {
        onClick(clear->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    del->setOnMouseOver([del, &window, this]() {
        window.beginDraw();
        onHoverButton(del, window);
        drawGrid(*del, window);
        window.endDraw();
    });

    del->setOnMouseOut([del, &window, this]() {
        window.beginDraw();
        onMouseOut(del, window);
        drawGrid(*del, window);
        window.endDraw();
    });

    del->setOnClick([del, &map, calc, &window, this]() {
        onClick(del->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    divide->setOnMouseOver([divide, &window, this]() {
        window.beginDraw();
        onHoverButton(divide, window);
        drawGrid(*divide, window);
        window.endDraw();
    });

    divide->setOnMouseOut([divide, &window, this]() {
        window.beginDraw();
        onMouseOut(divide, window);
        drawGrid(*divide, window);
        window.endDraw();
    });

    divide->setOnClick([divide, &map, calc, &window, this]() {
        onClick(divide->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    seven->setOnMouseOver([seven, &window, this]() {
        window.beginDraw();
        onHoverButton(seven, window);
        drawGrid(*seven, window);
        window.endDraw();
    });

    seven->setOnMouseOut([seven, &window, this]() {
        window.beginDraw();
        onMouseOut(seven, window);
        drawGrid(*seven, window);
        window.endDraw();
    });

    seven->setOnClick([seven, &map, calc, &window, this]() {
        onClick(seven->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    eight->setOnMouseOver([eight, &window, this]() {
        window.beginDraw();
        onHoverButton(eight, window);
        drawGrid(*eight, window);
        window.endDraw();
    });

    eight->setOnMouseOut([eight, &window, this]() {
        window.beginDraw();
        onMouseOut(eight, window);
        drawGrid(*eight, window);
        window.endDraw();
    });

    eight->setOnClick([eight, &map, calc, &window, this]() {
        onClick(eight->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    nine->setOnMouseOver([nine, &window, this]() {
        window.beginDraw();
        onHoverButton(nine, window);
        drawGrid(*nine, window);
        window.endDraw();
    });

    nine->setOnMouseOut([nine, &window, this]() {
        window.beginDraw();
        onMouseOut(nine, window);
        drawGrid(*nine, window);
        window.endDraw();
    });

    nine->setOnClick([nine, &map, calc, &window, this]() {
        onClick(nine->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    multiply->setOnMouseOver([multiply, &window, this]() {
        window.beginDraw();
        onHoverButton(multiply, window);
        drawGrid(*multiply, window);
        window.endDraw();
    });

    multiply->setOnMouseOut([multiply, &window, this]() {
        window.beginDraw();
        onMouseOut(multiply, window);
        drawGrid(*multiply, window);
        window.endDraw();
    });

    multiply->setOnClick([multiply, &map, calc, &window, this]() {
        onClick(multiply->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    four->setOnMouseOver([four, &window, this]() {
        window.beginDraw();
        onHoverButton(four, window);
        drawGrid(*four, window);
        window.endDraw();
    });

    four->setOnMouseOut([four, &window, this]() {
        window.beginDraw();
        onMouseOut(four, window);
        drawGrid(*four, window);
        window.endDraw();
    });

    four->setOnClick([four, &map, calc, &window, this]() {
        onClick(four->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    five->setOnMouseOver([five, &window, this]() {
        window.beginDraw();
        onHoverButton(five, window);
        drawGrid(*five, window);
        window.endDraw();
    });

    five->setOnMouseOut([five, &window, this]() {
        window.beginDraw();
        onMouseOut(five, window);
        drawGrid(*five, window);
        window.endDraw();
    });

    five->setOnClick([five, &map, calc, &window, this]() {
        onClick(five->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    six->setOnMouseOver([six, &window, this]() {
        window.beginDraw();
        onHoverButton(six, window);
        drawGrid(*six, window);
        window.endDraw();
    });

    six->setOnMouseOut([six, &window, this]() {
        window.beginDraw();
        onMouseOut(six, window);
        drawGrid(*six, window);
        window.endDraw();
    });

    six->setOnClick([six, &map, calc, &window, this]() {
        onClick(six->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    minus->setOnMouseOver([minus, &window, this]() {
        window.beginDraw();
        onHoverButton(minus, window);
        drawGrid(*minus, window);
        window.endDraw();
    });

    minus->setOnMouseOut([minus, &window, this]() {
        window.beginDraw();
        onMouseOut(minus, window);
        drawGrid(*minus, window);
        window.endDraw();
    });

    minus->setOnClick([minus, &map, calc, &window, this]() {
        onClick(minus->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    one->setOnMouseOver([one, &window, this]() {
        window.beginDraw();
        onHoverButton(one, window);
        drawGrid(*one, window);
        window.endDraw();
    });

    one->setOnMouseOut([one, &window, this]() {
        window.beginDraw();
        onMouseOut(one, window);
        drawGrid(*one, window);
        window.endDraw();
    });

    one->setOnClick([one, &map, calc, &window, this]() {
        onClick(one->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    two->setOnMouseOver([two, &window, this]() {
        window.beginDraw();
        onHoverButton(two, window);
        drawGrid(*two, window);
        window.endDraw();
    });

    two->setOnMouseOut([two, &window, this]() {
        window.beginDraw();
        onMouseOut(two, window);
        drawGrid(*two, window);
        window.endDraw();
    });

    two->setOnClick([two, &map, calc, &window, this]() {
        onClick(two->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    three->setOnMouseOver([three, &window, this]() {
        window.beginDraw();
        onHoverButton(three, window);
        drawGrid(*three, window);
        window.endDraw();
    });

    three->setOnMouseOut([three, &window, this]() {
        window.beginDraw();
        onMouseOut(three, window);
        drawGrid(*three, window);
        window.endDraw();
    });

    three->setOnClick([three, &map, calc, &window, this]() {
        onClick(three->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    plus->setOnMouseOver([plus, &window, this]() {
        window.beginDraw();
        onHoverButton(plus, window);
        drawGrid(*plus, window);
        window.endDraw();
    });

    plus->setOnMouseOut([plus, &window, this]() {
        window.beginDraw();
        onMouseOut(plus, window);
        drawGrid(*plus, window);
        window.endDraw();
    });

    plus->setOnClick([plus, &map, calc, &window, this]() {
        onClick(plus->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    zero->setOnMouseOver([zero, &window, this]() {
        window.beginDraw();
        onHoverButton(zero, window);
        drawGrid(*zero, window);
        window.endDraw();
    });

    zero->setOnMouseOut([zero, &window, this]() {
        window.beginDraw();
        onMouseOut(zero, window);
        drawGrid(*zero, window);
        window.endDraw();
    });

    zero->setOnClick([zero, &map, calc, &window, this]() {
        onClick(zero->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    point->setOnMouseOver([point, &window, this]() {
        window.beginDraw();
        onHoverButton(point, window);
        drawGrid(*point, window);
        window.endDraw();
    });

    point->setOnMouseOut([point, &window, this]() {
        window.beginDraw();
        onMouseOut(point, window);
        drawGrid(*point, window);
        window.endDraw();
    });

    point->setOnClick([point, &map, calc, &window, this]() {
        onClick(point->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
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

    equals->setOnMouseOver([equals, &window, this]() {
        window.beginDraw();
        onHoverButton(equals, window);
        drawGrid(*equals, window);
        window.endDraw();
    });

    equals->setOnMouseOut([equals, &window, this]() {
        window.beginDraw();
        onMouseOut(equals, window);
        drawGrid(*equals, window);
        window.endDraw();
    });

    equals->setOnClick([equals, &map, calc, &window, this]() {
        onClick(equals->getText(), map, calc);
        window.beginDraw();
        auto& display = map.at("display");
        auto& coords = display->getAbsoluteCoords();
        // TODO: write a 'clear' function for window that takes a grid element and paints it to the colour of its container's background, ensure handles background colours that are nullopt (paint 0x000000?).
        window.rectangle(coords[0] == 0.00 ? coords[0] : coords[0] - 1, coords[1] == 0 ? coords[1] : coords[1] - 1, coords[2] + 1, coords[3] + 1, display->getContainer()->getBackgroundColor(), std::nullopt);
        drawGrid(*map.at("display"), window);
        window.endDraw();
    });

    map.emplace(equals->getId(), equals);
    
}