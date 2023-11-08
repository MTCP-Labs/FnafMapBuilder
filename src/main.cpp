#include <raylib.h>
#include "fnafmap.hpp"
 
int main(void) {

    std::vector<fnaf::ui::fnaf_menu_title> menu_titles = {
        (fnaf::ui::fnaf_menu_title) { "Welcome to the FNAF 3D Map Builder", 30, 100 },
        (fnaf::ui::fnaf_menu_title) { "Left Click to begin building", 25, 30 }
    };
    fnaf::ui::fnaf_menu menu(menu_titles);

    InitWindow(WIDTH, HEIGHT, TITLE);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(WIDTH - 6 * 12, 0);
        // Menu Handling
        menu.load_menu();
        menu.handle_input();
        // End Menu Handling
        // Build Scene
        if (!menu.is_menu()) {
            DrawText("Build Mode Active", 10, 10, 30, GREEN);
        }
        // End Build Scene
        EndDrawing();
    }

    CloseWindow();
}