CC = gcc
CFLAGS = -g -Wall -O2 $(shell sdl2-config --cflags)
LIBS := $(shell sdl2-config --libs) -lSDL2_ttf

SRC = main.c
EXEC = main

.PHONY: all
all: $(SRC)
	@echo "CC $<"
	@gcc $(CFLAGS) $< -o $(EXEC) $(LIBS)

.PHONY: run
run: $(EXEC)
	@./main

.PHONY: clean
clean:
	rm -rf $(EXEC)
