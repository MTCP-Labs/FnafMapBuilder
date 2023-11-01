SRC=src
BUILD=build

.PHONY: build

all: build

build: $(SRC)/main.cpp
	g++ -std=c++14 $< $(SRC)/**/*.cpp -I./include -o $(BUILD)/FnafBuilder.o `pkg-config raylib --libs --cflags pkg-config nlohmann_json --cflags`

run: $(BUILD)/FnafBuilder.o
	./$<