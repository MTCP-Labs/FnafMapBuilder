#include <raylib.h>
#include <string.h>

#include "log.hpp"
#include "modelex.hpp"

#define MENU_START_X 10
#define MENU_START_Y 10

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "GAME");
    SetWindowState(FLAG_WINDOW_MAXIMIZED);
    DisableCursor();                                 
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
    std::string input;

    bool isMenuDisplayed = true;
    bool isModelInitialized = false;

    ModelEx model_man;
    Texture2D texture;

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) 
    {
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed(KEY_F2)) {       // Reset the camera
            camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
            camera.target = zeroes;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };     
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (!isMenuDisplayed && IsKeyPressed(KEY_F1)) {     // Display menu
                isMenuDisplayed = true;
            }

            if (isMenuDisplayed && IsKeyPressed(KEY_ENTER)) {      // Hide menu
                isMenuDisplayed = false;

                texture = LoadTexture("models/guy.png");               
                model_man = ModelEx(LoadModel("models/guy.iqm"), (Vector3){0.0f, stof(input), 0.0f}, (Vector3){1.0f, 0.0f, 0.0f}, -90.0f, ones);        // Initialize ModelEx 
                SetMaterialTexture(&(model_man.model).materials[0], MATERIAL_MAP_DIFFUSE, texture);  

                isModelInitialized = true;
            } 
            
            if(isMenuDisplayed) {
                int key = GetCharPressed();     // Get new y-coordinate of the model as input 
                if (key >= (int) '0' && key <= (int) '9' || key == (int) '-') {
                    input += (char) key;
                }

                if (IsKeyPressed(KEY_BACKSPACE)) {
                    input.pop_back();
                }
                
                // Draw menu
                DrawRectangle(0, 0, screenWidth / 4, screenHeight, Fade(SKYBLUE, 0.5f));
                DrawRectangleLines(0, 0, screenWidth / 4, screenHeight, BLUE);    
                DrawText("ENTER MODEL POS_Y: ", MENU_START_X, MENU_START_Y, 20, GREEN);
                DrawText(input.c_str(), 244, MENU_START_Y, 20, RED);
            }

            if(!isMenuDisplayed && isModelInitialized) {
                BeginMode3D(camera);

                    model_man.draw();
                    DrawGrid(10, 1.0f);

                EndMode3D();
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadTexture(texture);     // Unload texture
    UnloadModel(model_man.model);       // Unload model  

    CloseWindow();     

    return 0;
}