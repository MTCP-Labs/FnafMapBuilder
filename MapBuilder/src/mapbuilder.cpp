#include "mapbuilder.hpp"

MapBuilder::MapBuilder(ModelEx modelEx, Camera3D camera): modelEx(modelEx), camera(camera) {
    init_modelex_property_list();
    init_input_box_list();
}

MapBuilder::MapBuilder(ModelEx modelEx, Camera3D camera, KeyboardKey CUSTOM_MENU_KEY): modelEx(modelEx), camera(camera), MENU_KEY(CUSTOM_MENU_KEY) {
    init_modelex_property_list();
    init_input_box_list();
}

MapBuilder::~MapBuilder() {}

float MapBuilder::text_size(int fontSize, int len) {
    const float FONT_SIZE_FACTOR = 0.7;
    return FONT_SIZE_FACTOR * fontSize * len;
}

void MapBuilder::init_modelex_property_list() {
    modelex_property_list[0][0] = &modelEx.position.x;
    modelex_property_list[0][1] = &modelEx.position.y;
    modelex_property_list[0][2] = &modelEx.position.z;

    modelex_property_list[1][0] = &modelEx.rotationAxis.x;
    modelex_property_list[1][1] = &modelEx.rotationAxis.y;
    modelex_property_list[1][2] = &modelEx.rotationAxis.z;

    modelex_property_list[2][0] = &modelEx.scale.x;
    modelex_property_list[2][1] = &modelEx.scale.y;
    modelex_property_list[2][2] = &modelEx.scale.z;
}

void MapBuilder::init_input_box_list() {
    const int INPUT_BOX_START_X = MENU_START_X + text_size(20, 2);
    const int INPUT_BOX_START_Y = MENU_START_Y;

    const int MAX_DIGITS = 6;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(i == 1) {
                inputBoxList[i][j] = InputBox(INPUT_BOX_START_X + j * text_size(20, MAX_DIGITS + 3), INPUT_BOX_START_Y + (i + 1) * text_size(20, 4), text_size(20, MAX_DIGITS), 20, std::to_string((int) (*modelex_property_list[i][j] * modelEx.rotationAngle)), RED);
            }
            else {
                inputBoxList[i][j] = InputBox(INPUT_BOX_START_X + j * text_size(20, MAX_DIGITS + 3), INPUT_BOX_START_Y + (i + 1) * text_size(20, 4), text_size(20, MAX_DIGITS), 20, std::to_string((int) *modelex_property_list[i][j]), RED);
            }
        }
    }
}

void MapBuilder::draw_input_box_list() {
    const char* coordinates[3] = { "X:", "Y:", "Z:"};
    const char* propertyNames[3] = {"POSITION", "ROTATION", "SCALE"};


    for(int i = 0; i < 3; i++) {
        DrawText(propertyNames[i], MENU_START_X, inputBoxList[i][0].pos_y - text_size(20, 2), 20, DARKGREEN);
        
        for(int j = 0; j < 3; j++) {
            DrawText(coordinates[j], inputBoxList[i][j].pos_x - text_size(20, 2), inputBoxList[i][j].pos_y, 20, DARKGREEN);
            inputBoxList[i][j].draw();
        }
    }
}

void MapBuilder::set_infocus_input_box() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(inputBoxList[i][j].in_focus()) {
                inputBoxList[i][j].isInFocus = true;
                inFocusInputBox = &inputBoxList[i][j];
            }
        }
    }
}

void MapBuilder::reset_infocus_input_box() {
    if(inFocusInputBox) {
        inFocusInputBox->isInFocus = false;
        inFocusInputBox = nullptr;
    }
}

void MapBuilder::update_modelex() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(i == 1 && inputBoxList[i][j].text != "0") {
                modelEx.rotationAngle = stof(inputBoxList[i][j].text);
                *modelex_property_list[i][j] = 1;
            }
            else {
                *modelex_property_list[i][j] = stof(inputBoxList[i][j].text);
            }
        }
    }
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
            update_modelex();
            reset_infocus_input_box();

            DisableCursor();        // Disable cursor for the game
        } 
        
        // Get new y-coordinate of the model as input 
        if(isMenuDisplayed) {
            // Draw menu
            DrawRectangle(0, 0, screenWidth / 4, screenHeight, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(0, 0, screenWidth / 4, screenHeight, BLUE);    

            // Handle input
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { 
                set_infocus_input_box();
            }

            if(inFocusInputBox) {
                inFocusInputBox->get_input();
            }

            draw_input_box_list();
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