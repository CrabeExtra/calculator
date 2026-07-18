cmake_minimum_required(VERSION 3.10)

project(Calculator)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(CalculatorWin WIN32 src/main_win.cpp)

target_link_libraries(CalculatorWin
    core
    platform
    ui
    app
    layout
)

add_custom_command(TARGET CalculatorWin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:CalculatorWin>/resources
)

add_custom_command(TARGET CalculatorWin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:CalculatorWin>/assets
)