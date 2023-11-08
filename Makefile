SRC:=src
BUILD:=build

.PHONY: run

all: run

$(BUILD)/FnafBuilder: $(SRC)/main.cpp
	if [ ! -d "build" ]; then \
		mkdir build; \
	fi
	g++ -std=c++14 $< -I./include -o $(BUILD)/FnafBuilder `pkg-config raylib --libs --cflags pkg-config nlohmann_json --cflags`

run: $(BUILD)/FnafBuilder
	./$<