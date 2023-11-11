#include <raylib.h>
#include <mapbuilder.hpp>

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "GAME");
    SetWindowState(FLAG_WINDOW_MAXIMIZED);                               
    SetTargetFPS(60);

    // Global Constants
    const Vector3 zeroes = {0.0f, 0.0f, 0.0f}, ones = {1.0f, 1.0f, 1.0f};

    // Define the camera (3D)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = zeroes;                      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE; 
    
    // Initialize the map builder
    ModelEx man_model = ModelEx(LoadModel("models/guy.iqm"), LoadTexture("models/guy.png"), zeroes, (Vector3){1.0f, 0.0f, 0.0f}, -90.0f, ones);
    MapBuilder mb = MapBuilder(man_model, camera);
    //--------------------------------------------------------------------------------------

    while(!WindowShouldClose()) {
        mb.init_map_builder(screenWidth, screenHeight);
    }  

    UnloadModel(man_model.model);
    UnloadTexture(man_model.texture);

    CloseWindow();
}