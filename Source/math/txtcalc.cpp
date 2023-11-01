#include "math/txtcalc.h"
#include <raylib.h>

static int midpoint(unsigned int screen_size, unsigned int len) {
    return (screen_size - len) / 2;
}

int calc_midpointx(unsigned int width, unsigned int len) {
    return midpoint(width, len);
}

int calc_midpointy(unsigned int height, unsigned int len) {
    return midpoint(height, len);
}