SOURCES = $(wildcard *.cpp)

all:
	nasm -f win64 heavens_gate.asm -o heavens_gate.o
	x86_64-w64-mingw32-g++ -static -masm=intel $(SOURCES) heavens_gate.o -o a.exe -lpsapi
