#include "ui/fnaf_menu.hpp"
#include "math/txtcalc.h"
#include <raylib.h>

using namespace fnaf::ui;

fnaf_menu::fnaf_menu(const std::vector<fnaf_menu_title> menu_text) : m_titles(menu_text) {
    this->m_on_menu = true;
}

void fnaf_menu::load_menu() noexcept {
    if (this->m_on_menu) {

        for (int i = 0; i < this->m_titles.size(); i++) {
            int len = MeasureText(this->m_titles[i].content.c_str(), this->m_titles[i].f_size);
            Vector2 pos = { (float) calc_midpointx(WIDTH, len), (float) calc_midpointy(HEIGHT, len) + (float) this->m_titles[i].yoffset };
            DrawText(this->m_titles[i].content.c_str(), pos.x, pos.y, this->m_titles[i].f_size, WHITE);
        }
        // const char* text = "test lol";
        // int font_size = 50;
        // int len = MeasureText(text, font_size);
        // Vector2 pos = { (float) calc_midpointx(WIDTH, len), (float) calc_midpointy(HEIGHT, len) };
        // DrawText(text, pos.x, pos.y, font_size, WHITE);
    }
}

void fnaf_menu::handle_input() noexcept {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && this->m_on_menu) {
        this->m_on_menu = false;
    }
}

const bool fnaf_menu::is_menu() const noexcept {
    return this->m_on_menu;
}
