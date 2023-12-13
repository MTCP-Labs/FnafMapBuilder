#include <raylib.h>
#include <mapbuilder.hpp>

#include <iostream>

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "GAME");
    SetWindowState(FLAG_WINDOW_MAXIMIZED);                               
    SetTargetFPS(60);

    // Define the camera (3D)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};                      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE; 
    
    // Initialize the Map Builder
    MapBuilder mb = MapBuilder();

    Model turret_model = LoadModel("models/obj/turret.obj");
    mb.add("turret", &turret_model);        // Add the model "turret" to the Map Builder
    Texture2D turret_texture = LoadTexture("models/obj/turret_diffuse.png");
    mb.set_material_texture("turret", MATERIAL_MAP_DIFFUSE, &turret_texture);

    Model house_model = LoadModel("models/obj/house.obj");
    mb.add("house", &house_model);      // Add the model "house" to the Map Builder
    Texture2D house_texture = LoadTexture("models/obj/house_diffuse.png");
    mb.set_material_texture("house", MATERIAL_MAP_DIFFUSE, &house_texture);
    //--------------------------------------------------------------------------------------

    while(!WindowShouldClose()) {
        // Ignore when running the Map Builder
        //----------------------------------------------------------------
        // UpdateCamera(&camera, CAMERA_FREE);        
        // mb.draw_all_models();
        //----------------------------------------------------------------
        mb.update_map_builder();
    }  

    mb.unload();

    CloseWindow();

    return 0;
}