#include <raylib.h>
#include "fnafmap.hpp"

int main(void) {

    std::vector<fnaf::ui::fnaf_menu_title> menu_titles = {
        (fnaf::ui::fnaf_menu_title) { "Welcome to the FNAF 3D Map Builder", 30, 100 },
        (fnaf::ui::fnaf_menu_title) { "Left Click to begin building", 25, 30 }
    };
    fnaf::ui::fnaf_menu menu(menu_titles);

    InitWindow(WIDTH, HEIGHT, TITLE);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        // Menu Handling
        menu.load_menu();
        menu.handle_input();
        // End Menu Handling
        // Build Scene
        if (!menu.is_menu()) {
            ClearBackground(BLUE);
        }
        // End Build Scene
        EndDrawing();
    }

    CloseWindow();
}