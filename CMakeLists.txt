cmake_minimum_required(VERSION 2.6)
project(huios)

set(CMAKE_CXX_FLAGS_DEBUG "-g -pg -ggdb -Wall -std=c++11 -Wno-reorder")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -std=c++11 -Wno-reorder")
set(CMAKE_SHARED_LINKER_FLAGS "-pg -g")
add_definitions(-pg -Wall -ggdb -std=c++11)
include_directories(/usr/local/ /usr/local/include/ ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
set(EXTLIBS sfml-graphics sfml-window sfml-system sfml-audio sfml-network GL
    GLEW glut GLU Xrandr cef cef_dll_wrapper)

set(SRCS
    ./include/huios.h
    ./include/browser_client.h
    ./include/render_handler.h
    ./include/request_handler.h
    ./include/browser_app.h
    ./include/render_process_handler.h
    ./include/js_value.h
    ./huios.cpp
    ./browser_client.cpp
    ./render_handler.cpp
    ./request_handler.cpp
    ./browser_app.cpp
    ./render_process_handler.cpp
    ./js_value.cpp
)

add_library(huios ${SRCS})

add_subdirectory(examples)
