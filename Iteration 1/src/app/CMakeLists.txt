add_library(app
    app.cpp
    app_mouse.cpp
    app_keyboard.cpp
)

target_link_libraries(app
    ui
    log
)

target_include_directories(app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)