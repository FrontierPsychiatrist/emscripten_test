cmake_minimum_required(VERSION 3.0)

project(emscripten_test)

add_executable(sdl_test main.c)

include(FindPkgConfig)
pkg_search_module(SDL required sdl)
include_directories(${SDL_INCLUDE_DIRS})

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    set(EXTRA_LIBS ${COCOA_LIBRARY})
endif(APPLE)

target_link_libraries(sdl_test ${SDL_LIBRARIES} ${EXTRA_LIBS})
