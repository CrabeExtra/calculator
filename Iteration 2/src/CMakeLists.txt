
add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(app)

add_library(src INTERFACE)

target_link_libraries(src INTERFACE
    core
    ui
    app
)