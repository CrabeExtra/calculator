
add_subdirectory(grid_engine)

add_library(lib INTERFACE)

target_link_libraries(lib INTERFACE
    grid_engine
)