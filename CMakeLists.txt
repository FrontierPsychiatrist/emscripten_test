cmake_minimum_required(VERSION 3.0)

project(emscripten_test)

add_executable(sdl_test main.c render.c)

include(FindPkgConfig)
pkg_search_module(SDL2 required sdl2)
pkg_search_module(SDL2IMAGE required SDL2_image)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    set(EXTRA_LIBS ${COCOA_LIBRARY})
endif(APPLE)

if(USE_EMSCRIPTEN)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2")
endif(USE_EMSCRIPTEN)

target_link_libraries(sdl_test ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES}  ${EXTRA_LIBS})
