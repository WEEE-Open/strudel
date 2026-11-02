# Makefile for the asdSaver screensaver

CC       = gcc
CFLAGS   = -Wall -Wextra -O2 -std=c11
LDFLAGS  = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET   = build/main
SRC      = $(wildcard src/*.c)
OBJ      = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ) | build
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
