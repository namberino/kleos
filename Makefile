CC = $(shell which clang)
CC ?= $(shell which gcc) # fallback compiler

C_SRC = $(wildcard src/*.c)
HEADERS = $(wildcard include/*.h)
OBJ = $(patsubst src/%.c, obj/%.o, $(C_SRC))

CFLAGS = -std=c11 -Wall -pedantic -Iinclude

compile: bin/chess

run: compile
	./bin/chess

bin/chess: $(OBJ) | bin
	"$(CC)" -o $@ $(OBJ)

bin:
	mkdir -p bin

obj/%.o: src/%.c $(HEADERS) | obj
	"${CC}" $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -f bin/* obj/*.o
