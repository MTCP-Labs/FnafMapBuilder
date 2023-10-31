#include <raylib.h>
#include "fnafmap.hpp"

int main(void) {
    InitWindow(WIDTH, HEIGHT, TITLE);

    std::vector<fnaf::ui::fnaf_menu_title> test;
    fnaf::ui::fnaf_menu menu(test);
    bool r = menu.is_menu();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
}