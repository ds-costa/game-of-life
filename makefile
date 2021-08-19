CC := g++
CFLAGS := -Wall -I"lib/raylib" -L"lib/raylib/ubuntu" -lraylib -lm  -lGL -lpthread -ldl -lrt -lX11
BIN := bin/life
SRC := src
SRCS := $(wildcard $(SRC)/*.cpp)

.PHONY: all

all:
	$(CC) main.cpp $(SRCS) $(CFLAGS) -o $(BIN) 

run:
	./$(BIN)

clean:
	rm $(BIN)