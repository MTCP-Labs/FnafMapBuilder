#include "ui/fnaf_menu.hpp"
#include <raylib.h>

using namespace fnaf::ui;

fnaf_menu::fnaf_menu(const std::vector<fnaf_menu_title> menu_text) : m_titles(menu_text) { }

void fnaf_menu::load_menu() noexcept {
    if (this->m_on_menu) {
        // render menu
    }
}

void fnaf_menu::handle_input() noexcept {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !this->m_on_menu) {
        this->m_on_menu = true;
    }
}

const bool fnaf_menu::is_menu() const noexcept {
    return this->m_on_menu;
}
