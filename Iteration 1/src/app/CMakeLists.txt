add_library(app
    app.cpp
)

target_include_directories(app PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)