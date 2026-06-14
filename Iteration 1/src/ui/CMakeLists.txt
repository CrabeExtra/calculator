add_library(ui
    display.cpp
    calculatorGui.cpp
)

target_link_libraries(ui
    layout
    platform
)

target_include_directories(ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)