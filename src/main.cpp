#include <raylib.h>
#include <string.h>

#include "log.hpp"
#include "modelex.hpp"
#include "input_box.hpp"

#define MENU_START_X 10
#define MENU_START_Y 10

float text_size(int fontSize, int len) {
    const float FONT_SIZE_FACTOR = 0.65;
    return FONT_SIZE_FACTOR * fontSize * len;
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "GAME");
    SetWindowState(FLAG_WINDOW_MAXIMIZED);                               
    SetTargetFPS(60);  

    // Global Constants
    const Vector3 zeroes = {0.0f, 0.0f, 0.0f};
    const Vector3 ones = {1.0f, 1.0f, 1.0f};

    // Define the camera (3D)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = zeroes;                      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;          

    // Global variables
    bool isMenuDisplayed = true;
    bool isModelInitialized = false;

    ModelEx me_man;
    Texture2D texture;

    InputBox ib_pos_y = InputBox(MENU_START_X + text_size(20, 18), MENU_START_Y, text_size(20, 6), 20, "0", RED);       // Initialize input box
    std::string *input = &ib_pos_y.text;

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) 
    {
        UpdateCamera(&camera, CAMERA_FREE);

        // Reset the camera
        if (IsKeyPressed(KEY_F2)) {       
            camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
            camera.target = zeroes;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };     
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Display menu
            if (!isMenuDisplayed && IsKeyPressed(KEY_F1)) {     
                isMenuDisplayed = true;
                EnableCursor();     // Enable cursor for the menu
            }

            // Hide menu
            if (isMenuDisplayed && IsKeyPressed(KEY_ENTER)) {   
                isMenuDisplayed = false;
                ib_pos_y.isInFocus = false;

                //Initialize model
                texture = LoadTexture("models/guy.png");               
                me_man = ModelEx(LoadModel("models/guy.iqm"), (Vector3){0.0f, stof(*input), 0.0f}, (Vector3){1.0f, 0.0f, 0.0f}, -90.0f, ones);        // Initialize ModelEx 
                SetMaterialTexture(&(me_man.model).materials[0], MATERIAL_MAP_DIFFUSE, texture);  
                isModelInitialized = true;

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

            if(!isMenuDisplayed && isModelInitialized) {
                // Begin 3D scene
                BeginMode3D(camera);

                    me_man.draw(); 
                    DrawGrid(1000, 1.0f);

                EndMode3D();
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadTexture(texture);     // Unload texture
    UnloadModel(me_man.model);       // Unload model  

    CloseWindow();     

    return 0;
}