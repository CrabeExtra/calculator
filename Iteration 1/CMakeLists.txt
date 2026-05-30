cmake_minimum_required(VERSION 3.10)

project(Calculator)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/core)
add_subdirectory(src/platform)
add_subdirectory(src/ui)
add_subdirectory(src/app)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(CalculatorWin WIN32 src/main_win.cpp)

target_link_libraries(CalculatorWin
    core
    platform
    ui
    app
)

