CC = $(shell which clang)
CC ?= $(shell which gcc) # fallback compiler

C_SRC = $(wildcard src/*.c)
HEADERS = $(wildcard include/*.h)
OBJ = $(patsubst src/%.c, obj/%.o, $(filter-out src/main%.c, $(C_SRC)))

CFLAGS = -std=c11 -Wall -pedantic -Iinclude
GLFLAGS = -lSDL2 -lSDL2_image

compile: bin/graphics

run: compile
	./bin/chess

run_graphics: compile
	./bin/graphics

bin/chess: $(OBJ) | bin
	"$(CC)" -o $@ $(OBJ)

bin/graphics: $(OBJ) | bin
	"$(CC)" -o $@ $(OBJ) $(GLFLAGS)

bin:
	mkdir -p bin

obj/%.o: src/%.c $(HEADERS) | obj
	"${CC}" $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -f bin/* obj/*.o
