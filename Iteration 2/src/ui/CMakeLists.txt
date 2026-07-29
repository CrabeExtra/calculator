add_library(ui
    ui.cpp
    calculatorGui.cpp
)

target_link_libraries(ui
    layout
    platform
    core
    grid_engine
)

target_include_directories(ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)