MAPBUILDER_ROOT=../

MAPBUILDER_SRC:=../src
MAPBUILDER_INCLUDE:=../include

SRC=src
BUILD:=build

OBJ_FILE=example

.PHONY: all run clean

all: run

$(BUILD): 
	mkdir build

run: $(BUILD)
	g++ -std=c++20 $(MAPBUILDER_SRC)/*.cpp $(SRC)/*.cpp -I$(MAPBUILDER_INCLUDE) -o$(BUILD)/$(OBJ_FILE) `pkg-config raylib --libs --cflags pkg-config nlohmann_json --cflags`
	./$(BUILD)/$(OBJ_FILE)

clean: $(BUILD)
	rm -rf $(BUILD)