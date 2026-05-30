add_subdirectory(win32)

add_library(platform INTERFACE)

target_link_libraries(platform INTERFACE win_platform)