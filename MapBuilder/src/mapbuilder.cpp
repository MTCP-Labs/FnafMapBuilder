#include "mapbuilder.hpp"

#include <iostream>

MapBuilder::MapBuilder() : ModelList() {
    init_camera();
}

MapBuilder::~MapBuilder() {}

void MapBuilder::init_camera() {
    camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; 
    camera.target = zeroes;                      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE; 
}

float MapBuilder::text_size(int fontSize, int len) {
    const float FONT_SIZE_FACTOR = 0.7;
    return FONT_SIZE_FACTOR * fontSize * len;
}


void MapBuilder::init_input_box_list() {
    const int INPUT_BOX_START_X = MENU_START_X + text_size(20, 2);
    const int INPUT_BOX_START_Y = MENU_START_Y;

    const int MAX_DIGITS = 6;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(i == 1 && propertyList[i][j] == 1) {
                inputBoxList[i][j] = InputBox(INPUT_BOX_START_X + j * text_size(20, MAX_DIGITS + 3), INPUT_BOX_START_Y + (i + 1) * text_size(20, 4) + 10, text_size(20, MAX_DIGITS), 20, TextFormat("%.2f", propertyList[i][j] * (rotationAngle * RAD2DEG)), RED);
            }
            else {
                inputBoxList[i][j] = InputBox(INPUT_BOX_START_X + j * text_size(20, MAX_DIGITS + 3), INPUT_BOX_START_Y + (i + 1) * text_size(20, 4) + 10, text_size(20, MAX_DIGITS), 20, TextFormat("%.2f", propertyList[i][j]), RED);
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
            if(inputBoxList[i][j].is_in_focus()) {
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


void MapBuilder::init_property_list() {
    Matrix t = inFocusModel->transform;

    // printf("Transformation Matrix:\n");
    // printf("[ %f, %f, %f, %f ]\n", t.m0, t.m4, t.m8, t.m12);
    // printf("[ %f, %f, %f, %f ]\n", t.m1, t.m5, t.m9, t.m13);
    // printf("[ %f, %f, %f, %f ]\n", t.m2, t.m6, t.m10, t.m14);
    // printf("[ %f, %f, %f, %f ]\n", t.m3, t.m7, t.m11, t.m15);

    // Update position of the model
    propertyList[0][0] = t.m12;
    propertyList[0][1] = t.m13;
    propertyList[0][2] = t.m14;

    // Update rotation of the model
    Vector3 rotationAxis;
    QuaternionToAxisAngle(QuaternionFromMatrix(t), &rotationAxis, &rotationAngle);

    propertyList[1][0] = (int) rotationAxis.x;
    propertyList[1][1] = (int) rotationAxis.y;
    propertyList[1][2] = (int) rotationAxis.z;

    // Update scale of the model
    propertyList[2][0] = Vector3Length((Vector3){ t.m0, t.m1, t.m2 });
    propertyList[2][1] = Vector3Length((Vector3){ t.m4, t.m5, t.m6 });
    propertyList[2][2] = Vector3Length((Vector3){ t.m8, t.m9, t.m10 });

    init_input_box_list();
}

void MapBuilder::set_transform() {
    Matrix translation = MatrixTranslate(propertyList[0][0], propertyList[0][1], propertyList[0][2]);
    Matrix rotation = MatrixRotate((Vector3) {propertyList[1][0], propertyList[1][1], propertyList[1][2]}, rotationAngle);
    Matrix scale = MatrixScale(propertyList[2][0], propertyList[2][1], propertyList[2][2]);

    inFocusModel->transform = MatrixMultiply(scale, MatrixMultiply(rotation, translation));
}

void MapBuilder::update_infocus_model() {
    bool isRotationAngleZero = true;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            inputBoxList[i][j].text = TextFormat("%.2f", stof(inputBoxList[i][j].text));
            if(i == 1 && stof(inputBoxList[i][j].text) != 0) {
                isRotationAngleZero = false;
                rotationAngle = stof(inputBoxList[i][j].text) * DEG2RAD;
                propertyList[i][j] = 1;
            }
            else {
                propertyList[i][j] = stof(inputBoxList[i][j].text);
            }
        }
    }

    if(isRotationAngleZero) {
        rotationAngle = 0.0f;
        propertyList[1][0] = 1;     // Set an arbitrary rotation axis if rotation angle is zero
    }

    set_transform();
}

void MapBuilder::update_map_builder() {
    if(modelList.size() == 0) {
        std::cerr << "ERROR: No Models in the Map Builder!" << std::endl;
        exit(0);
    }

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    UpdateCamera(&camera, CAMERA_FREE);

    // Vector3 movement = { 0.0f, 0.0f, 0.0f };
    // Vector3 rotation = { 0.0f, 0.0f, 0.0f };
    // float zoom = 0.0f;

    // // Calculate the forward vector based on the position and target
    // Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));

    // // Camera movement with WASD keys
    // if (IsKeyDown(KEY_W)) movement = Vector3Scale(Vector3CrossProduct(camera.up, forward), 1.0f);
    // if (IsKeyDown(KEY_S)) movement = Vector3Scale(Vector3CrossProduct(forward, camera.up), 1.0f);
    // if (IsKeyDown(KEY_A)) movement.y -= 1.0f;
    // if (IsKeyDown(KEY_D)) movement.y += 1.0f;

    // // Camera rotation with arrow keys
    // if (IsKeyDown(KEY_UP)) rotation.y -= 1.0f;
    // if (IsKeyDown(KEY_DOWN)) rotation.y += 1.0f;
    // if (IsKeyDown(KEY_LEFT)) rotation.x -= 1.0f;
    // if (IsKeyDown(KEY_RIGHT)) rotation.x += 1.0f;

    // // Camera zoom based on mouse wheel movement
    // zoom = GetMouseWheelMove();

    // UpdateCameraPro(&camera, movement, rotation, zoom);
    
    if (IsKeyPressed(CAMERA_RESET_KEY)) {       
        init_camera();
    }

    BeginDrawing();

        ClearBackground(RAYWHITE);

        // Menu
        //--------------------------------------------------------------------------------------
        // Display menu
        if (!isMenuDisplayed && IsKeyPressed(MENU_KEY)) {
            inFocusModelId = get_infocus_model_id(camera);
            inFocusModel = get(inFocusModelId);
            
            if(inFocusModel) {     
                isMenuDisplayed = true;
                
                init_property_list();       // Update property list of the model in focus using it's transformation matrix

                EnableCursor();     // Enable cursor for the menu
            }
        }

        // Hide menu
        if (isMenuDisplayed && IsKeyPressed(KEY_ENTER)) {   
            isMenuDisplayed = false;

            update_infocus_model();
            reset_infocus_input_box();

            DisableCursor();       // Disable cursor for the map builder
        } 
        
        if(isMenuDisplayed) {
            // Draw menu
            DrawRectangle(0, 0, screenWidth / 4, screenHeight, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(0, 0, screenWidth / 4, screenHeight, BLUE);    

            // Handle input
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { 
                set_infocus_input_box();
            }

            if(inFocusInputBox) {
                inFocusInputBox->get_float_input();
            }

            DrawText("MODEL ID: ", MENU_START_X, MENU_START_Y + 10, 20, DARKGREEN);
            DrawText(inFocusModelId.c_str(), text_size(20, 9), MENU_START_Y + 10, 20, YELLOW);
            draw_input_box_list();
        }
        //--------------------------------------------------------------------------------------

        if(!isMenuDisplayed) {
            DrawCircle(screenWidth / 2, screenHeight / 2, 5.0f, DARKPURPLE);        // Draw crosshair

            // Begin 3D scene
            BeginMode3D(camera);

                draw_all_models();
                DrawGrid(1000, 10.0f);

            EndMode3D();
        }

    EndDrawing();
}