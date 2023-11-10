#ifndef __INPUT_BOX_HPP__
#define __INPUT_BOX_HPP__

#include <raylib.h>
#include <iostream>
#include "log.hpp"

class InputBox {
public:
    int pos_x, pos_y, width, height;
    std::string text;
    Color color;
    bool isInFocus = false;
    
    InputBox();
    InputBox(int pos_x, int pos_y, int width, int height, std::string text, Color color);
    ~InputBox();

    void draw();
    void in_focus();
    void get_input();
};

#endif /*__INPUT_BOX_HPP__*/
