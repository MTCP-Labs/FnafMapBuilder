MAPBUILDER_ROOT=MapBuilder
MAPBUILDER_SRC:=$(MAPBUILDER_ROOT)/src
MAPBUILDER_INCLUDE:=$(MAPBUILDER_ROOT)/include

SRC=src
INCLUDE=include
BUILD:=build

.PHONY: all run clean

all: run

$(BUILD): 
	mkdir build

run: $(BUILD)
	g++ -std=c++20 $(MAPBUILDER_SRC)/*.cpp $(SRC)/*.cpp -I$(MAPBUILDER_INCLUDE) -I$(INCLUDE) -o$(BUILD)/main `pkg-config raylib --libs --cflags pkg-config nlohmann_json --cflags`
	./$(BUILD)/main

clean: $(BUILD)
	rm -rf $(BUILD)