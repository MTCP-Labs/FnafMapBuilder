SRC=src
BUILD=build
INCLUDE=include
FILE=main

if [ ! $# -eq 0 ]; then
    SRC=practice_src
    BUILD=practice_build
    FILE=$1
fi

if [ ! -d "build" ]; then 
    mkdir build
fi 

g++ -std=c++20 $SRC/*.cpp -I$INCLUDE -o$BUILD/$FILE -Werror `pkg-config raylib --libs --cflags pkg-config nlohmann_json --cflags`

./$BUILD/$FILE