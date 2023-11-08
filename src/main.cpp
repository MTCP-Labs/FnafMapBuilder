#include <raylib.h>
#include <string.h>

#include "log.hpp"

void init_model(Model &model, Texture2D &texture, std::string input) {
    model = LoadModel(("models/" + input + ".iqm").c_str());                    // Load the animated model mesh and basic data
    texture = LoadTexture(("models/" + input + ".png").c_str());                // Load model texture and set material
    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);     // Set model material map texture
}

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

    const Vector3 origin = {0.0f, 0.0f, 0.0f};

    // Define the camera (3D)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = origin;                      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;          

    // Model Initialization
    Model model;
    Texture2D texture;

    // Global variables
    std::string input;
    bool isMenuDisplayed = true;
    bool isModelInitialized = false;

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) 
    {
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed(KEY_F2)) {       // Reset the camera
            camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
            camera.target = origin;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };     
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (!isMenuDisplayed && IsKeyPressed(KEY_F1)) {     // Open menu
                isMenuDisplayed = true;
            }

            if (isMenuDisplayed && IsKeyPressed(KEY_ENTER)) {      // Close menu
                isMenuDisplayed = false;
                init_model(model, texture, input);
                isModelInitialized = true;
            } 
            
            if(isMenuDisplayed) {
                int key = GetCharPressed();     // Get model name as input 
                if (key != 0) {
                    input += (char) key;
                }

                if (IsKeyPressed(KEY_BACKSPACE)) {
                    input.pop_back();
                }
                
                DrawRectangle(0, 0, screenWidth / 4, screenHeight, Fade(SKYBLUE, 0.5f));
                DrawRectangleLines(0, 0, screenWidth / 4, screenHeight, BLUE);    
                DrawText("ENTER MODEL NAME: ", 10, 10, 20, GREEN);
                DrawText(input.c_str(), 236, 10, 20, RED);
            }

            if(!isMenuDisplayed && isModelInitialized) {
                BeginMode3D(camera);

                        DrawModelEx(model, origin, (Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
                        DrawGrid(10, 1.0f);

                EndMode3D();
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadTexture(texture);     // Unload texture
    UnloadModel(model);         // Unload model  

    CloseWindow();     

    return 0;
}
