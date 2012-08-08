CC = g++
FILES = src/cart.cpp \
        src/emulator.cpp \
        src/main.cpp \
        src/oam.cpp \
        src/disassembler.cpp \
        src/input.cpp \
        src/mmu.cpp \
        src/cpu.cpp \
        src/header.cpp \
        src/ppu.cpp

LIBS = -lglut -lGL -lGLU
FLAGS = -Wall
OUT = mnes

all: $(FILES)
	$(CC) $(FLAGS) -o $(OUT) $(FILES) $(LIBS)

clean:
	rm -f *.o $(OUT)
