# Map Builder for raylib games

This is a 3D Map Builder for games to be made using [raylib](https://www.raylib.com/) with C++

### About
- The Map Builder provides a *menu* for allowing real-time changes of the properties of a 3D model in the world, essentially *building a map*    
- The menu can be instatntiated by pressing the `MENU_KEY` which is `KEY_F1` by default, and `KEY_ENTER` saves the modified properties

![image](https://github.com/Kaushik-Kalesh/MapBuilder/assets/67593056/774b1b8e-36c2-44cc-914e-60976cc48741)  

- As shown in the image, the properties avaiable for changes are namely *position*, *rotation* and *scale* of a model

### Installation
Clone this repo, and then install the following dependencies:
- raylib [guide](https://github.com/raysan5/raylib/blob/master/README.md)
- nlohmann-json [guide](https://json.nlohmann.me/integration/package_managers/#cocoapods)
- pkg-config (for [examples](MapBuilder/examples/)) [guide](https://www.google.com/search?q=pkg-config+install&oq=pkg-config+install&sourceid=chrome&ie=UTF-8)

### Example
A sample client usage can be found at [client.cpp](MapBuilder/examples/src/client.cpp)
```cpp
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
```

Run the following in GNU/Linux or MacOS to build and run the example:
```bash
cd MapBuilder/examples
make
```

Check [examples](MapBuilder/examples/) for more info

### Credits
Created by shab & Kaushik Kalesh

`Copyright (C) 2023 MTCP-Labs. All Rights Reserved.`
