add_library(layout
    grid.cpp
)

target_include_directories(layout PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)