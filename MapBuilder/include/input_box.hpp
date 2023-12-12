#ifndef __INPUT_BOX_HPP__
#define __INPUT_BOX_HPP__

#include <raylib.h>
#include <string>

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
    bool is_in_focus();
    void get_float_input();
};

#endif /*__INPUT_BOX_HPP__*/
