Emscripten SDL2 Test with CMake
===============================

Small test project to build a SDL2 program with both emscripten
and native.

Building
========

Native
------
To build native you must have SDL2 installed.

    mkdir build
    cd build
    cmake ..
    make

Emscripten
----------
To build with emscripten you need to have emscripten installed.

    mkdir build_js
    cd build_js
    emcmake cmake -DCMAKE_C_FLAGS="-s USE_SDL=2" ..
    make

To generate a usable HTML page (this seems to be hacky...)

    cd build_js
    make
    emcc CMakfeFiles/sdl_test/main.c.o -s USE_SDL=2 -o main.html
    open main.html

(open is a OSX command, just open the main.html file)

Program
=======
You can change the screen color with a mouse click and quit
with q or escape.
