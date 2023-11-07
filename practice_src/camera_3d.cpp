#include <raylib.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "3D Camera");
    SetWindowState(FLAG_WINDOW_MAXIMIZED);
    DisableCursor();                                 

    const Vector3 origin = {0.0f, 0.0f, 0.0f};

    // Define the camera (3D)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = origin;                      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;            

    Mesh cubeMesh = GenMeshCube(2.0f, 2.0f, 2.0f);
    Model cubeModel = LoadModelFromMesh(cubeMesh);
    Vector3 cubePosition = {0.0f, 1.0f, 0.0f};

    SetTargetFPS(60);  
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) 
    {
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyDown('Z')) {       // Reset the camera
            camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
            camera.target = origin;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };     
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawModel(cubeModel, cubePosition, 1.0f, RED);      // Draw the model
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
                
                DrawCube(origin, 10.0f, 0.1f, 10.0f, GREEN);        // Draw the ground
                DrawCubeWires(origin, 10.0f, 0.1f, 10.0f, DARKGREEN);

            EndMode3D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();     

    return 0;
}