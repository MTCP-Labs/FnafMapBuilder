#include "mapbuilder.hpp"

MapBuilder::MapBuilder(ModelEx modelEx, Camera3D camera): modelEx(modelEx), camera(camera) {
    ib_pos_y = InputBox(MENU_START_X + text_size(20, 18), MENU_START_Y, text_size(20, 6), 20, "0", RED);
}

MapBuilder::MapBuilder(ModelEx modelEx, Camera3D camera, KeyboardKey CUSTOM_MENU_KEY): modelEx(modelEx), camera(camera), MENU_KEY(CUSTOM_MENU_KEY) {
    ib_pos_y = InputBox(MENU_START_X + text_size(20, 18), MENU_START_Y, text_size(20, 6), 20, "0", RED);
}

MapBuilder::~MapBuilder() {}

float MapBuilder::text_size(int fontSize, int len) {
    const float FONT_SIZE_FACTOR = 0.65;
    return FONT_SIZE_FACTOR * fontSize * len;
}

void MapBuilder::init_map_builder(int screenWidth, int screenHeight) {
    UpdateCamera(&camera, CAMERA_FREE);

    // Reset the camera (for debugging purposes only)
    if (IsKeyPressed(KEY_F2)) {       
        camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
        camera.target = zeroes;
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };     
    }
    
    BeginDrawing();

        ClearBackground(RAYWHITE);

        // Menu
        //--------------------------------------------------------------------------------------
        // Display menu
        if (!isMenuDisplayed && IsKeyPressed(MENU_KEY)) {     
            isMenuDisplayed = true;
            EnableCursor();     // Enable cursor for the menu
        }

        // Hide menu
        if (isMenuDisplayed && IsKeyPressed(KEY_ENTER)) {   
            isMenuDisplayed = false;
            ib_pos_y.isInFocus = false;     
            modelEx.position.y = std::stof(ib_pos_y.text);

            DisableCursor();        // Disable cursor for the game
        } 
        
        // Get new y-coordinate of the model as input 
        if(isMenuDisplayed) {
            // Draw menu
            DrawRectangle(0, 0, screenWidth / 4, screenHeight, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(0, 0, screenWidth / 4, screenHeight, BLUE);    
            DrawText("ENTER MODEL POS_Y:", MENU_START_X, MENU_START_Y, 20, DARKGREEN);

            // Handle input
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { 
                ib_pos_y.in_focus();
            }

            if(ib_pos_y.isInFocus) {
                ib_pos_y.get_input();
            }

            ib_pos_y.draw();
        }
        //--------------------------------------------------------------------------------------

        if(!isMenuDisplayed) {
            // Begin 3D scene
            BeginMode3D(camera);

                modelEx.draw(); 
                DrawGrid(1000, 1.0f);

            EndMode3D();
        }

    EndDrawing();
}