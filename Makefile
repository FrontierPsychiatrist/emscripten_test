all:
	cc -lSDLmain -lSDL -Wl,-framework,Cocoa main.c

emscripten:
	emcc main.c -o main.html

check-syntax:
	cc -o nul -S main.c
