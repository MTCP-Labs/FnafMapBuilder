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
    mb.add("turret", &turret_model);        // Add the model to the map builder
    Texture2D turret_texture = LoadTexture("models/obj/turret_diffuse.png");
    mb.set_material_texture("turret", MATERIAL_MAP_DIFFUSE, &turret_texture);

    Model house_model = LoadModel("models/obj/house.obj");
    mb.add("house", &house_model);      // Add the model to the map builder
    Texture2D house_texture = LoadTexture("models/obj/house_diffuse.png");
    mb.set_material_texture("house", MATERIAL_MAP_DIFFUSE, &house_texture);
    //--------------------------------------------------------------------------------------

    while(!WindowShouldClose()) {
        // UpdateCamera(&camera, CAMERA_FREE);        // Ignore your camera when running the map builder
        mb.init_map_builder();
    }  

    mb.unload_all_models();
    mb.unload_all_textures();

    CloseWindow();
}