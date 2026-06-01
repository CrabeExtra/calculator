
add_library(win_platform
    window.cpp
    window_draw.cpp
)

target_link_libraries(win_platform PRIVATE
    d2d1
    dxgi
    dwrite
)