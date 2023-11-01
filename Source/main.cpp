#include <raylib.h>
#include "fnafmap.hpp"

int main(void) {

    std::vector<fnaf::ui::fnaf_menu_title> menu_titles = {
        (fnaf::ui::fnaf_menu_title) { "Welcome to the FNAF 3D Map Builder", 30, 100 },
        (fnaf::ui::fnaf_menu_title) { "Left Click to begin building", 40, 150 }
    };
    fnaf::ui::fnaf_menu menu(menu_titles);

    InitWindow(WIDTH, HEIGHT, TITLE);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        menu.load_menu();
        EndDrawing();
    }

    CloseWindow();
}