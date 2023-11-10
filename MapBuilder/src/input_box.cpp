#include "input_box.hpp"

InputBox::InputBox() {}

InputBox::InputBox(int pos_x, int pos_y, int width, int height, std::string text, Color color): pos_x(pos_x), pos_y(pos_y), width(width), height(height), text(text), color(color) {}

InputBox::~InputBox() {}

void InputBox::draw() {
    DrawRectangle(pos_x, pos_y, width, height, WHITE);
    DrawText(text.c_str(), pos_x + 0.05 * width, pos_y, height, color);
}

void InputBox::in_focus() {
    int mouse_x = GetMouseX(), mouse_y = GetMouseY();
    isInFocus = (mouse_x >= pos_x && mouse_x <= pos_x + width) && (mouse_y >= pos_y && mouse_y <= pos_y + height);
}

void InputBox::get_input() {
    int key = GetCharPressed();     
    if (key >= (int) '0' && key <= (int) '9' || key == (int) '-') {
        if(text[0] == '0') {
            text.pop_back();
        }
        text.push_back(key);
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        text.pop_back();
        if (text.size() == 0) {
            text.push_back('0');
        }
    }
}