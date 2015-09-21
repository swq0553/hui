cmake_minimum_required(VERSION 2.6)
project(hui)

set(CMAKE_CXX_FLAGS_DEBUG "-g -pg -ggdb -Wall -std=c++11 -Wno-reorder")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -std=c++11 -Wno-reorder")
set(CMAKE_SHARED_LINKER_FLAGS "-pg -g")
add_definitions(-pg -Wall -ggdb -std=c++11)
include_directories(/usr/local/ /usr/local/include/ ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
set(EXTLIBS sfml-graphics sfml-window sfml-system sfml-audio sfml-network GL
    GLEW glut GLU Xrandr cef cef_dll_wrapper cpptest)

set(SRCS
    ./include/hui.h
    ./include/browser_client.h
    ./include/render_handler.h
    ./include/request_handler.h
    ./include/browser_app.h
    ./include/render_process_handler.h
    ./include/js_value.h
    ./src/hui.cpp
    ./src/browser_client.cpp
    ./src/render_handler.cpp
    ./src/request_handler.cpp
    ./src/browser_app.cpp
    ./src/render_process_handler.cpp
    ./src/js_value.cpp
)

add_library(hui ${SRCS})

add_subdirectory(examples)
add_subdirectory(tests)
