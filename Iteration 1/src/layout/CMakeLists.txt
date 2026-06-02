add_library(layout
    grid.cpp
)


target_link_libraries(layout
    log
)

target_include_directories(layout PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)