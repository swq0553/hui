project(cefui)
include_directories(/usr/local/ /usr/local/include/ ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_executable(cefui_basic main.cpp)
target_link_libraries(cefui_basic cefui ${EXTLIBS})
