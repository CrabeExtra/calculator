cmake_minimum_required(VERSION 3.10)

project(Calculator)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(CalculatorWin WIN32 src/main_win.cpp)

install(TARGETS CalculatorWin
    RUNTIME DESTINATION .
)

install(DIRECTORY resources/
    DESTINATION resources
)

target_link_libraries(CalculatorWin
    src
    lib
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


# import library resources.
file(GLOB LIB_DIRS LIST_DIRECTORIES true ${CMAKE_CURRENT_SOURCE_DIR}/lib/*)

foreach(LIB_DIR ${LIB_DIRS})
    if(IS_DIRECTORY ${LIB_DIR}/resources)
        message(STATUS "Found resources: ${LIB_DIR}/resources")
        get_filename_component(LIB_DIR_NAME ${LIB_DIR} NAME)
        add_custom_target(copy_${LIB_DIR_NAME}_resources ALL
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${LIB_DIR}/resources/
            $<TARGET_FILE_DIR:CalculatorWin>/resources
        )
    endif()
endforeach()