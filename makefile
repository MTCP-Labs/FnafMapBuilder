
all: build

build:
	g++ -std=c++14 Source/main.cpp -I./include -o Build/FnafBuilder `pkg-config raylib --libs --cflags pkg-config nlohmann_json --cflags`

run:
	./Build/FnafBuilder

.PHONY: build