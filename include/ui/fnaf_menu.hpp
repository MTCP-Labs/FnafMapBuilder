#ifndef __FNAF_MENU_HPP__
#define __FNAF_MENU_HPP__

#include <vector>
#include <string>

namespace fnaf {
namespace ui {

typedef struct fnaf_menu_title {
    std::string content;
    unsigned int f_size;
    unsigned int c_count;
} fnaf_menu_title;

class fnaf_menu final {
private:
    std::vector<fnaf_menu_title> m_titles;
    bool m_on_menu;
public:
    fnaf_menu(const std::vector<fnaf_menu_title>);
    ~fnaf_menu() = default;
public:
    void load_menu() noexcept;
    void handle_input() noexcept;
    const bool is_menu() const noexcept;
};

}
}

#endif /* __FNAF_MENU_HPP__ */