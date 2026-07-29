add_library(app
    app.cpp
)

target_link_libraries(app
    ui
    log
    core
    grid_engine
)

target_include_directories(app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)