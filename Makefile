SRC:=src
BUILD:=build
INCLUDE:=include

.PHONY: all run clean

all: run

$(BUILD): 
	mkdir build

run: $(BUILD)
	g++ -std=c++20 $(SRC)/*.cpp -I$(INCLUDE) -o$(BUILD)/main `pkg-config raylib --libs --cflags pkg-config nlohmann_json --cflags`
	./$(BUILD)/main

clean: $(BUILD)
	rm -rf $(BUILD)