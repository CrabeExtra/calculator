add_library(core
    calculator.cpp
)

target_link_libraries(core
    log
)

target_include_directories(core  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)